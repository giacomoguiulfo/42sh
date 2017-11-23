/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:02:17 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:51:49 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <stdlib.h>
#include <unistd.h>

int		msh_exit(char **args)
{
	(void)args;
	return (0);
}

int		msh_help(char **args)
{
	ft_putstr("************************************************************\n");
	ft_putstr("*                        Minishell                         *\n");
	ft_putstr("* -------------------------------------------------------- *\n");
	ft_putstr("* Author:        gguiulfo                                  *\n");
	ft_putstr("* Contact:       gguiulfo@student.42.us.org                *\n");
	ft_putstr("* Description:   A simple shell made in C.                 *\n");
	ft_putstr("*                By Odin, by Thor! Use the shell!!!        *\n");
	ft_putstr("* Builtin Commands:                                        *\n");
	ft_putstr("*      echo -- cd -- setenv -- unsetenv -- env -- exit     *\n");
	ft_putstr("************************************************************\n");
	(void)args;
	return (1);
}

void	echo_esc_chr(char esc)
{
	if (esc == '"')
		write(1, "\"", 1);
	else if (esc == '\'')
		write(1, "\'", 1);
	else if (esc == 'b')
		write(1, "\b", 1);
	else if (esc == 'f')
		write(1, "\f", 1);
	else if (esc == 'n')
		write(1, "\n", 1);
	else if (esc == 'r')
		write(1, "\r", 1);
	else if (esc == 't')
		write(1, "\t", 1);
	else if (esc == 'v')
		write(1, "\v", 1);
	else if (esc == '\\')
		write(1, "\\", 1);
}

int		msh_env_inval(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ISUPPER(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int		msh_senv_helper(char *str, t_darr *newenvp, char *tmp)
{
	int index;

	index = msh_env_idx(newenvp, str);
	free(ft_darr_remove(newenvp, index));
	ft_darr_set(newenvp, index, tmp);
	return (1);
}
