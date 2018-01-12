/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:11:15 by giacomo           #+#    #+#             */
/*   Updated: 2018/01/11 16:42:01 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "libft.h"
#include <stddef.h>
#include <stdbool.h>

static char			*get_optarg(char ***av, char *arg)
{
	if (!arg || !*arg || !*(arg + 1))
	{
		(*av)++;
		return (**av);
	}
	return (*(arg + 1) == '=' ? arg + 2 : arg + 1);
}

static int			invalid_optarg(t_optsdata *optsdata, t_opt *opt, bool name)
{
	if (name)
		ft_dprintf(STDERR_FILENO, "%s: option '--%s' requires an argument\n",
		optsdata->prog, opt->name);
	else
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- '%c'\n",
		optsdata->prog, opt->c);
	if (optsdata->help)
		ft_opts_suggest(optsdata);
	return (1);
}

static inline void	load_flag(void *data, t_opt *opt)
{
	((t_optparser *)data)->flags |= opt->flags_on;
	((t_optparser *)data)->flags &= ~opt->flags_off;
}

int					ft_opts_short(char ***av, t_optsdata *optsdata, void *data)
{
	t_opt	*opt;
	char	*opt_name;
	char	*opt_arg;
	int		i;

	opt_name = **av + 1;
	i = -1;
	while (opt_name[++i])
	{
		opt_arg = NULL;
		if (!(opt = ft_opts_getshort(optsdata->opt_map, opt_name[i])))
			return (ft_opts_usage(optsdata, opt, NULL, opt_name[i]));
		load_flag(data, opt);
		if (opt->getarg)
		{
			if (opt->arg_required && !(opt_arg = get_optarg(av, opt_name + i))
				&& !opt->def_val)
				return (invalid_optarg(optsdata, opt, false));
			if (opt->getarg(opt->def_val, opt_arg, data))
				return (invalid_optarg(optsdata, opt, false));
			if (opt->arg_required)
				break ;
		}
	}
	return ((*av)++ ? 0 : 0);
}

int					ft_opts_long(char ***av, t_optsdata *optsdata, void *data)
{
	t_opt	*opt;
	char	*opt_name;
	char	*opt_arg;

	opt_name = **av + 2;
	opt = ft_opts_getlong(optsdata->opt_map, opt_name);
	if (!opt && optsdata->help && ft_strequ(opt_name, "help"))
		return (ft_opts_help(optsdata));
	if (!opt)
		return (ft_opts_usage(optsdata, opt, opt_name, 0));
	load_flag(data, opt);
	if (opt->getarg)
	{
		opt_arg = NULL;
		if (opt->arg_required && !(opt_arg = get_optarg(av, NULL)) &&
																!opt->def_val)
			return (invalid_optarg(optsdata, opt, true));
		if (opt->getarg(opt->def_val, opt_arg, data))
			return (invalid_optarg(optsdata, opt, true));
	}
	(*av)++;
	return (0);
}
