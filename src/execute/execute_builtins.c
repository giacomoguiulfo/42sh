/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"
#include "parser.h"

t_strfmap	g_builtins[] =
{
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
	{"export", &builtin_export},
	{"history", &builtin_history},
	{"read", &builtin_read},
	{"local", &builtin_setenv},
	{"setenv", &builtin_setenv},
	{"unset", &builtin_unset},
	{"unsetenv", &builtin_unsetenv},
	{NULL, NULL}
};

int			aget_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}

t_builtin	*msh_run_builtin(t_asttoken *this)
{
	int i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(g_builtins[i].name, this->binary) == 0)
			return (g_builtins[i].f);
		i++;
	}
	return (NULL);
}
