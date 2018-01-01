/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:11:18 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/24 13:56:05 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

#define EXP_OPT_LP			(1 << 0)
#define EXP_HAS_OPT_LP(a)	(a & EXP_OPT_LP)

static t_optsdata g_expopts =
{
	"export", NULL, NULL, NULL, 0, true, 0, {
		{'p', NULL, NULL, NULL, NULL, EXP_OPT_LP, 0, NULL, 0, 0},
		{0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	}
};

static int	export_variables(char **av)
{
	int		ret;
	char	*value;

	ret = 0;
	while (*av)
	{
		value = ft_strchr(*av, '=');
		if (value)
		{
			*value = '\0';
			value++;
		}
		else
			value = ft_getenv(sh_singleton()->localenv, *av);
		ret += builtin_setenv((char*[]){"export", *av, value, NULL});
		builtin_unsetenv((char*[]){"local", *av, NULL});
		av++;
	}
	return ((ret) ? 1 : 0);
}

static int	export_print(void)
{
	char	**env;
	char	*set;

	env = sh_singleton()->env;
	while (*env)
	{
		set = ft_strchr(*env, '=');
		if (set && !set[1])
			ft_printf("export %.*s\n", set - *env, *env);
		else
			ft_printf("export %s\n", *env);
		env++;
	}
	return (0);
}

int			builtin_export(char **avº)
{
	t_optparser data;

	data.flags = 0;
	if (ft_opts(avº, &g_expopts, &data, true))
		return (1);
	if (EXP_HAS_OPT_LP(data.flags))
		return (export_print());
	if (!*(data.argv))
		return (export_print());
	return (export_variables(data.argv));
}
