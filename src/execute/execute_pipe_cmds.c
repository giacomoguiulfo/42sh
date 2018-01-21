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

int		msh_run_prog_a(char *executable, char **args, char **newenvp, t_astree *node, char *path, int in, int out);

void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path, int in, int out)
{
	this_path = build_bin_path(path, node->this->binary);
	setup_io(shell, node->this->redirs);
	if (this_path)
		node->ret = msh_run_prog_a(this_path, node->this->args, shell->env, node, path, in, out);
}

int		msh_run_prog_a(char *executable, char **args, char **newenvp, t_astree *node, char *path, int in, int out)
{
	pid_t	pid;
	int		status;
	char 	*test;
	t_builtin *builtin;

	test = NULL;
	pipe(node->pipe_fd);
	node->pid = fork();
	if (node->pid == 0)
	{
		if (node->prev)
			child_pipe(sh_singleton(), node->prev, test, path, node->pipe_fd[0], node->pipe_fd[1]);
		close(node->pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	else if (node->pid < 0)
	{
		ft_dprintf(2, "Trash: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (WIFEXITED(&status));
		if (out != 1)
			dup2(out, 1);
		if (node->prev)
			dup2(node->pipe_fd[0], 0);
		if (!node->prev)
			close(node->pipe_fd[0]);
		close(node->pipe_fd[1]);
		if ((builtin = msh_run_builtin(node->this->binary)))
			node->ret = builtin((const char **)node->this->args);
		else
		{
			if (execve(executable, args, newenvp) == -1)
				ft_dprintf(2, "Trash: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
	}
	sh_init_termios();
	return (status);
}

t_astree *get_end(t_astree *node)
{
	while (node->right && node->right->type && node->right->type[0] == '|')
		node = node->right;
	node = node->right;
	return (node);
}

t_astree *piped_execution(t_shell *shell, t_astree *node, char *this_path, char *path)
{
	int 		pid;
	int 		status;
	t_astree 	*end;

	end = get_end(node);
	pid = fork();
	if (pid == 0)
		child_pipe(shell, end, this_path, path, 0, 1);
	else
		wait(&status);
	return (end);
}



