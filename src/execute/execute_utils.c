/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execyte_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "execute.h"
#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool	try_pwd(char *binary)
{
	char		cwd_path[MAX_PATH];
	char		*ptr;
	struct stat sb;

	ptr = cwd_path;
	getcwd(ptr, MAX_PATH);
	ft_strcat(cwd_path, "/");
	ft_strcat(cwd_path, binary);
	if ((lstat(cwd_path, &sb)) == -1)
		return (false);
	else if (!check_access(cwd_path))
		return (false);
	else if (!check_reg_file(sb.st_mode))
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
