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
void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path, int in, int out);

int		msh_run_prog_a(char *executable, char **args, char **newenvp, t_astree *node, char *path, int in, int out)
{
	pid_t	pid;
	int 	pipefd[2];
	int		status;
	char 	*test;

	test = NULL;
	pipe(pipefd);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipefd[0]);
		if (node->prev)
		{
			ft_dprintf(2, "Spawning child: %s\n", node->prev->this->binary);
			child_pipe(sh_singleton(), node->prev, test, path, pipefd[0], pipefd[1]);
		}
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
		ft_dprintf(2, "Parent after waitpid: %s\n", executable);
		ft_dprintf(2, "Out: %d, In: %d\n", out, in);
		if (out != 1)
		{
			ft_dprintf(2, "Using output FD: %d\n", out);
			dup2(out, 1);
		}
		else
			ft_dprintf(2, "Using output FD: 1\n");
		if (node->prev)
		{
			ft_dprintf(2, "Using input FD: %d\n", pipefd[0]);
			dup2(pipefd[0], 0);
		}
		ft_dprintf(2, "%d-->%s\n", pid, executable);
		close(pipefd[0]);
		close(pipefd[1]);
		if (execve(executable, args, newenvp) == -1)
		{
			ft_dprintf(2, "Trash: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
	}
	sh_init_termios();
	return (status);
}

void	child_pipe(t_shell *shell, t_astree *node, char *this_path, char *path, int in, int out)
{
	this_path = build_bin_path(path, node->this->binary);
	ft_dprintf(2, "path: %s\n", this_path);
	if (this_path)
		node->ret = msh_run_prog_a(this_path, node->this->args, shell->env, node, path, in, out);
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

t_astree *piped_execution(t_shell *shell, t_astree *node, char *this_path, char *path)
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
		child_pipe(shell, end, this_path, path, 0, 1);
	}
	else
	{
		wait(&status);
		ft_dprintf(2, "finished piped execution completely\n");
		dup2(sh_singleton()->stdin_backup, 0);
		dup2(sh_singleton()->stdout_backup, 1);
	}
	return (end);
}



