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


int		msh_run_prog_a(char *executable, char **args, char **newenvp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_dprintf(2, "-->%s\n", executable);
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
	sh_init_termios();
	return (status);
}

void	execute_links(t_shell *shell, t_astree *node, char *this_path, char *path);

void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	this_path = build_bin_path(path, node->this->binary);
	if (this_path)
		node->ret = msh_run_prog_a(this_path, node->this->args, shell->env);
	close(pipefd[1]);
}

void	parent_pipe(t_shell *shell, t_astree *node, char *this_path, char *path, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	if (node->prev && node->prev->type && node->prev->type[0] == '|' && node->prev->type[1] != '|')
	{
		ft_dprintf(2, "getting the next link...\n");
		execute_links(shell, node->prev, this_path, path);
	}
	else
	{
		child_pipe(shell, node, this_path, path, pipefd);
	}
	close(pipefd[0]);
}

void	execute_links(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	int pid;
	int pipefd[2];
	int status;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_dprintf(2, "child pipe\n");
		child_pipe(shell, node, this_path, path, pipefd);
	}
	else
	{
		ft_dprintf(2, "parent pipe\n");
		parent_pipe(shell, node, this_path, path, pipefd);
		waitpid(-1, &status, 0);
		exit(EXIT_SUCCESS);
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
		execute_links(shell, end, this_path, path);
	else
	{
		while ((waitpid(pid, &status, WNOHANG)) == 0)
			;
	}
}



