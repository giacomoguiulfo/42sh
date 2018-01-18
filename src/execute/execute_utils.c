/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2018/01/18 11:05:56 by gguiulfo         ###   ########.fr       */
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

bool	check_access(char *path)
{
	if (!((access(path, X_OK)) == 0))
	{
		return (false);
	}
	return (true);
}

bool	check_reg_file(mode_t st_mode)
{
	if (S_ISLNK(st_mode))
		return (true);
	if (S_ISREG(st_mode))
		return (true);
	return (false);
}

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

bool	try_without_path(char *test)
{
	struct stat sb;

	if ((lstat(test, &sb)) == -1)
		return (false);
	else if (!check_access(test))
		return (false);
	else if (!(sb.st_mode & S_IXUSR))
	{
		return (false);
	}
	return (true);
}
