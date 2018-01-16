/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:16:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/12 14:32:46 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

#define SENV_ERR_1 "setenv: Too many arguments."
#define SENV_ERR_2 "setenv: Variable name must begin with a letter."
#define SENV_ERR_3 "setenv: Variable name must contain alphanumeric characters."

static void	assign_var(char **av, char ***env)
{
	char	*str;
	int		i;

	ft_asprintf(&str, "%s=%s", av[1], (av[2]) ? av[2] : "");
	i = 0;
	while ((*env) && (*env)[i])
	{
		if (ft_strcmp((*env)[i], av[1]) == '=' &&
			ft_strlen(av[1]) == ft_strlenchr((*env)[i], '='))
		{
			ft_strdel(&(*env)[i]);
			(*env)[i] = str;
			return ;
		}
		i++;
	}
	*env = ft_sstrpush(*env, str);
	ft_strdel(&str);
}

int			builtin_setenv(char **av)
{
	char ***env;

	if (!av || !av[0])
		return (1);
	env = (!ft_strcmp(av[0], "local")) ?
		&sh_singleton()->localenv : &sh_singleton()->env;
	if (!av[1])
		ft_sstrputs(*env);
	else if (av[1] && av[2] && av[3])
		return (SH_ERR2_R1(SENV_ERR_1));
	else if (!ft_isalpha(av[1][0]) && av[1][0] != '_' && av[1][0] != '/')
		return (SH_ERR2_R1(SENV_ERR_2));
	else if (!ft_unixcase(av[1]))
		return (SH_ERR2_R1(SENV_ERR_3));
	else
		assign_var(av, env);
	return (0);
}
