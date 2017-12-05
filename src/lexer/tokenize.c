/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/wait.h>

char	*find_path(char *binary, char *path)
{
	struct stat sb;
	char		*try_this_path[MAX_PATH_BIN_SIZE];
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, MAX_PATH_BIN_SIZE);
		ft_strncpy((char*)try_this_path, start, end - start);
		ft_strcat((char*)try_this_path, "/");
		ft_strcat((char*)try_this_path, binary);
		if ((lstat((char*)try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, (char*)try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode))
				return (false);
			return (ft_strdup((const char*)try_this_path));
		}
		start = end + 1;
	}
	return (NULL);
}

void	tokenize(char	*instructions)
{
	char	**split;
	char	*path;
	char	*valid;
	pid_t	pid;
	int		status;

	ft_printf("Here are your instructions: %s\n", instructions);
	if (instructions)
		split = ft_strsplit(instructions, ' ');
	else
		return ;
	path = get_path();
	valid = find_path(split[0], path);
	ft_printf("%s\n", valid);
	pid = fork();
	if (pid == 0)
		execve(valid, split, sh_singleton()->env);
	wait(&status);
}

/*
void	msh_run_prog(char *executable, char **args, char **newenvp)
{
 	pid_t	pid;
 	int		status;

 	pid = fork();
 	if (pid == 0)
	{
		if (execve(executable, args, newenvp) == -1)
 		{
			ft_dprintf(2, "msh: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
 	}
 	else if (pid < 0)
 	{
		ft_dprintf(2, "msh: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
 	}
 	wait(&status);
}*/