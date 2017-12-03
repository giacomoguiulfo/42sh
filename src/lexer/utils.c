/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>

char	*get_path(void)
{
	t_shell	*shell;
	char	*path;
	int		x;

	shell = sh_singleton();
	x = -1;
	while (shell->env[++x])
	{
		if ((ft_strncmp(shell->env[x], "PATH=", 5)) == 0)
		{
			path = shell->env[x] + 5;
			return (path);
		}
	}
	return (NULL);
}

int		get_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}

bool	check_binary(char *binary, char *path, int *x)
{
	char	bin_name[4096];
	int		end;

	end = get_binary_size(binary);
	*x = *x + end;
	ft_bzero(bin_name, 4096);
	ft_strncpy(bin_name, binary, end);
	ft_printf("full binary: %s\n", binary);
	ft_printf("binary name: %s\n", bin_name);
	ft_printf("binary size: %d\n", end);
	ft_printf("path: %s\n", path);
	return (true);
}