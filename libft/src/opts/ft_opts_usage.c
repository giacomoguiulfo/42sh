/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opts_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:30:42 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/23 21:25:41 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "libft.h"
#include <unistd.h>
#include <stdbool.h>

int ft_opts_usage(t_optsdata *optsdata, t_opt *opt, char *name, char c)
{
	if (!optsdata->usage)
		return (1);
	if (name)
	{
		if (opt && opt->required)
			ft_dprintf(STDERR_FILENO, "%s: requried option '--%s'\n",
			optsdata->prog, opt->name);
		else
			ft_dprintf(STDERR_FILENO, "%s: unrecognized option '--%s'\n",
			optsdata->prog, name);
	}
	else if (c)
	{
		if (opt && opt->required)
			ft_dprintf(STDERR_FILENO, "%s: requried option -- '%c'\n",
			optsdata->prog, opt->c);
		else
			ft_dprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n",
			optsdata->prog, c);
	}
	if (optsdata->help)
		ft_opts_suggest(optsdata);
	return (1);
}
