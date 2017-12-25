/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:17:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/24 13:51:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

int builtin_unsetenv(char **av, char **envp __attribute__((unused)))
{
	char	***env;
	int		i;
	int		j;

	env = (!ft_strcmp(av[0], "local")) ? &sh_singleton()->localenv : &sh_singleton()->env;
	i = 0;
	while (av[i])
	{
		j = 0;
		while ((*env) && (*env)[j])
		{
			if (ft_strcmp((*env)[j], av[i]) == '=' &&
				ft_strlen(av[i]) == ft_strlenchr((*env)[j], '='))
				ft_sstrdel(*env, j);
			else
				j++;
		}
		i++;
	}
	return (0);
}
