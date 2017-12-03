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
#include <unistd.h>

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

bool	try_paths(char *binary, char *path, char *try_this_path)
{
	char	*start;
	char	*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, 4096);
		ft_strncpy(try_this_path, start, end - start);
		ft_strcat(try_this_path, "/");
		ft_strcat(try_this_path, binary);
		if ((access(try_this_path, X_OK)) == 0)
		{
			ft_printf("Lexer: access found for path %s\n", try_this_path);
			return (true);
		}
		start = end + 1;
	}
	return (false);
}

bool	check_binary(char *binary, char *path, int *x)
{
	char	bin_name[4096];
	char	valid_path[4096];
	char	*ptr;
	int		end;

	end = get_binary_size(binary);
	*x = *x + end;
	ptr = valid_path;
	ft_bzero(bin_name, 4096);
	ft_strncpy(bin_name, binary, end);
	if (try_paths(bin_name, path, ptr))
	{
		ft_printf("Lexer: bin %s has valid path %s\n", binary, valid_path);
		return (true);
	}
	ft_printf("Lexer: No valid path found, que triste :[\n");
	return (false);
}