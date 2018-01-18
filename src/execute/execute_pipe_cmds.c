/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2018/01/12 15:12:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "builtins.h"
#include "execute.h"
#include "ft_sh.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>

/*void	execution(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	t_builtin	*builtin;

	if ((builtin = msh_run_builtin(node->this->binary)))
		node->ret = builtin((const char **)node->this->args);
	else
	{
		if (try_without_path(node->this->binary))
		{
			node->ret = msh_run_prog(node->this->binary,
				node->this->args, shell->env);
		}
		else if ((this_path = build_bin_path(path, node->this->binary)))
		{
			node->ret = msh_run_prog(this_path,
				node->this->args, shell->env);
		}
	}
}*/

void	execute_links(t_shell *shell, t_astree *node, char *this_path, char *path);
void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path);

int		msh_run_prog_a(char *executable, char **args, char **newenvp, t_astree *node, char *path)
{
	pid_t	pid;
	int 	pipefd[2];
	int		status;
	char 	*test;

	test = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_dprintf(2, "-->%s\n", executable);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		if (execve(executable, args, newenvp) == -1)
		{
			ft_dprintf(2, "Trash: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_dprintf(2, "Trash: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		if (node->prev && node->prev->type && node->prev->type[0] == '|' && node->prev->type[1] != '|')
		{
			ft_dprintf(2, "getting the next link...\n");
			child_pipe(sh_singleton(), node->prev, test, path);
		}
		close(pipefd[0]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	sh_init_termios();
	return (status);
}

void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	this_path = build_bin_path(path, node->this->binary);
	if (this_path)
		node->ret = msh_run_prog_a(this_path, node->this->args, shell->env, node, path);
}

void	execute_links(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		ft_dprintf(2, "child pipe\n");
		child_pipe(shell, node, this_path, path);
	}
	else
	{
		ft_dprintf(2, "parent pipe\n");
		waitpid(-1, &status, 0);
	}
}

t_astree *get_end(t_astree *node)
{
	ft_dprintf(2, "getting end: %s\n", node->type);
	while (node->right && node->right->type && node->right->type[0] == '|')
	{
		ft_dprintf(2, "getting end: %s\n", node->type);
		node = node->right;
	}
	node = node->right;
	ft_dprintf(2, "getting end: %s\n", node->type);
	return (node);
}

void	piped_execution(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	int 		pid;
	int 		status;
	t_astree 	*end;

	ft_dprintf(2, "-Piped_execution start\n");

	end = get_end(node);
	ft_dprintf(2, "node end type: %s\n", end->type);
	pid = fork();
	ft_dprintf(2, "PID: %d\n", pid);
	if (pid == 0)
	{
		child_pipe(shell, end, this_path, path);
		dup2(sh_singleton()->stdin_backup, 0);
	}
	else
	{
		waitpid(-1, &status, 0);
		dup2(sh_singleton()->stdin_backup, 0);
	}
}



