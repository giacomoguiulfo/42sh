/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_build_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "execute.h"
#include <sys/stat.h>

bool	check_access(char *binary, char *path)
{
	if (!((access(path, X_OK)) == 0))
	{
		ft_printf("Lexer: permission denied: %s\n", binary);
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

char	*check_pwd(char *binary)
{
	char		cwd_path[MAX_PATH];
	char		*ptr;
	struct stat sb;

	ptr = cwd_path;
	getcwd(ptr, MAX_PATH);
	ft_strcat(cwd_path, "/");
	ft_strcat(cwd_path, binary);
	if ((lstat(cwd_path, &sb)) == -1)
		return (NULL);
	else if (!check_access(binary, cwd_path))
		return (NULL);
	else if (!check_reg_file(sb.st_mode))
		return (NULL);
	return (ft_hstrdup(cwd_path));
}

void	build_buffer(char buff[MAX_PATH], char *binary, char *start, char *end)
{
	ft_bzero((void*)buff, MAX_PATH);
	ft_strncpy(buff, start, end - start);
	ft_strcat(buff, "/");
	ft_strcat(buff, binary);
}

char	*build_bin_path(char *path, char *binary)
{
	char		*start;
	char		*end;
	char		buff[MAX_PATH];
	struct stat sb;

	start = path;
	while (start && ((end = ft_strchr(start, ':')) != NULL))
	{
		build_buffer(buff, binary, start, end);
		if ((lstat(buff, &sb)) != -1)
		{
			if (!check_access(binary, buff))
				return (NULL);
			else if (!check_reg_file(sb.st_mode))
				return (NULL);
			return (ft_hstrdup(buff));
		}
		start = end + 1;
	}
	if ((end = check_pwd(binary)))
		return (end);
	ft_printf("Kash: command not found: %s\n", binary);
	return (NULL);
}
