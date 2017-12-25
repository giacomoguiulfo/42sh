/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:11:12 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/24 17:02:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

#define UNSET_OPT_LF		(1 << 0)
#define UNSET_OPT_LV		(1 << 1)
#define UNSET_HAS_OPT_LF(a)	(a & UNSET_OPT_LF)
#define UNSET_HAS_OPT_LV(a)	(a & UNSET_OPT_LV)

static t_optsdata g_unsetopts =
{
	"unset", NULL, NULL, NULL, 0, true, 0, {
		{'f', NULL, NULL, NULL, NULL, UNSET_OPT_LF, UNSET_OPT_LV, NULL, 0, 0},
		{'v', NULL, NULL, NULL, NULL, UNSET_OPT_LV, UNSET_OPT_LF, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

int	builtin_unset(char **av)
{
	t_optparser data;
	char	*tmp;

	data.flags = 0;
	if (ft_opts(av, &g_unsetopts, &data, true))
		return (1);
	if (UNSET_HAS_OPT_LF(data.flags))
	{
		ft_printf("unset: functions not supported yet\n");
		return (0);
	}
	tmp = av[0];
	av[0] = "local";
	builtin_unsetenv(av, NULL);
	av[0] = tmp;
	builtin_unsetenv(av, NULL);
	return (0);
}
