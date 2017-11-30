/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:16:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/25 01:59:29 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

static void assign_var(char **av, char ***env)
{
	char	*str;
	int		i;

	ft_asprintf(&str, "%s=%s", av[1], av[2]);
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

int builtin_setenv(char **av, char **envp __attribute__((unused)))
{
	char ***env;

	if (!av || !av[0])
		return (1);
	env = &sh_singleton()->env;
	if (!av[1])
		ft_sstrputs(*env);
	else // TODO: Check that is a proper assignemnt - validations
		assign_var(av, env);
	return (0);
}