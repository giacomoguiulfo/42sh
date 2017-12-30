/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:09:18 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/23 13:27:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "libft.h"
#include <stdbool.h>

static int	validate_required(t_optsdata *optsdata, void *data)
{
	int i;

	if (!optsdata->required_opts)
		return (0);
	i = 0;
	while (optsdata->opt_map[i].c)
	{
		if (optsdata->opt_map[i].required &&
			!(((t_optparser *)data)->flags & optsdata->opt_map[i].flags_on))
		{
			return (ft_opts_usage(optsdata, &optsdata->opt_map[i],
					NULL, optsdata->opt_map[i].c));
		}
		i++;
	}
	return (0);
}

int			ft_opts(char **av, t_optsdata *optsdata, void *data, bool parse)
{
	if (!av)
		return (1);
	if (!optsdata->prog)
		optsdata->prog = *av;
	av++;
	while (av && *av)
	{
		if (!ft_strcmp(*av, "-") || (!ft_strcmp(*av, "--") && av++))
			break ;
		if ((*av)[0] == '-' && (*av)[1] == '-')
		{
			if (ft_opts_long(&av, optsdata, data))
				return (1);
		}
		else if ((*av)[0] == '-')
		{
			if (ft_opts_short(&av, optsdata, data))
				return (1);
		}
		else
			break ;
	}
	optsdata->argv = av;
	av = (parse) ? av : g_argv;
	((t_optparser *)data)->argv = av;
	return (validate_required(optsdata, data));
}
