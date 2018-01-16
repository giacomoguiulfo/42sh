/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_build_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2018/01/12 15:47:07 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "execute.h"
#include <sys/stat.h>

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
	else if (!check_access(cwd_path))
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

bool	check_again(char **start, char **end, char buff[MAX_PATH], char *binary)
{
	struct stat sb;

	build_buffer(buff, binary, *start, *end);
	if ((lstat(buff, &sb)) != -1)
	{
		if (!check_access(buff))
			return (false);
		else if (!check_reg_file(sb.st_mode))
			return (false);
		return (true);
	}
	*start = *end + 1;
	return (false);
}

char	*build_bin_path(char *path, char *binary)
{
	char		*start;
	char		*end;
	char		buff[MAX_PATH];

	if (path)
	{
		start = path;
		while (start && ((end = ft_strchr(start, ':')) != NULL))
		{
			if (check_again(&start, &end, buff, binary))
				return (ft_hstrdup(buff));
		}
		end = start + ft_strlen(start);
		if (check_again(&start, &end, buff, binary))
		{
			return (ft_hstrdup(buff));
		}
	}
	if ((end = check_pwd(binary)))
	{
		return (end);
	}
	ft_dprintf(2, "Trash: command not found: %s\n", binary);
	return (NULL);
}
