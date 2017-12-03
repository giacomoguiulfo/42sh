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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool	try_pwd(char *binary)
{
	char		cwd_path[4096];
	char		*ptr;
	struct stat sb;

	ptr = cwd_path;
	getcwd(ptr, 4096);
	ft_strcat(cwd_path, "/");
	ft_strcat(cwd_path, binary);
	if ((lstat(cwd_path, &sb)) == -1)
		return (false);
	else if (!check_access(binary, cwd_path))
		return (false);
	else if (!check_reg_file(sb.st_mode, binary))
		return (false);
	return (true);
}

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

bool	check_access(char *binary, char *path)
{
	if (!((access(path, X_OK)) == 0))
	{
		ft_printf("Lexer: permission denied: %s\n", binary);
		return (false);
	}
	return (true);
}

bool	check_reg_file(mode_t st_mode, char *binary)
{
	if (!S_ISREG(st_mode))
	{
		ft_printf("Lexer: command not found: %s\n", binary);
		return (false);
	}
	return (true);
}
