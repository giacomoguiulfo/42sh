/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execute_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>

/*
typedef struct			s_asttoken
{
	char				*binary;
	char				**args;
	struct s_tokelist	**redirs;
	struct s_tokelist	*chain;
}						t_asttoken;

typedef struct			s_astree
{
	struct s_asttoken	*this;
	struct s_astree		*left;
	struct s_astree		*right;	
}						t_astree;
*/
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
}
/*
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
	if (!S_ISREG(st_mode))
		return (false);
	return (true);
}

bool	try_paths(char *binary, char *path, char *try_this_path)
{
	struct stat sb;
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, MAX_PATH_BIN_SIZE);
		ft_strncpy(try_this_path, start, end - start);
		ft_strcat(try_this_path, "/");
		ft_strcat(try_this_path, binary);
		if ((lstat(try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode))
				return (false);
			return (true);
		}
		start = end + 1;
	}
	return (false);
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
}*/

char	*build_path111(char *path, char *binary)
{
	char		*start;
	char		*end;
	char		buff[MAX_PATH_BIN_SIZE];
	struct stat sb;

	ft_printf("1Inside build path\n");
	start = path;
	ft_printf("2Inside build path\n");
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)buff, MAX_PATH_BIN_SIZE);
		ft_strncpy(buff, start, end - start);
		ft_strcat(buff, "/");
		ft_strcat(buff, binary);
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
	return (NULL);
}

void	execute_ast_cmds(t_astree *head)
{
	t_shell	*shell;
	char	*path;
	char	*use_path;

	ft_printf("Welcome to cmd execution\n");
	shell = sh_singleton();
	path = NULL;
	path = get_path();
	ft_printf("After get path: %s\n", path);
	ft_printf("binary: %s\n", head->this->binary);
	use_path = build_path111(path, head->this->binary);
	ft_printf("After build path: %s\n", use_path);
	msh_run_prog(use_path, head->this->args, shell->env);
	//need path
	//need environment variables
}
