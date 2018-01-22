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

static void	child_process(t_pipeline this)
{
	if (this.end->prev)
	{
		this.end = this.end->prev;
		make_process(this, this.end->pipe_fd[1]);
	}
	close(this.end->pipe_fd[0]);
	exit(EXIT_SUCCESS);
}

static void	parent_process(t_pipeline this, int out)
{
	t_builtin *builtin;

	while (WIFEXITED(this.status))
		;
	if (out != 1)
		dup2(out, 1);
	if (this.end->prev)
		dup2(this.end->pipe_fd[0], 0);
	if (!this.end->prev)
		close(this.end->pipe_fd[0]);
	close(this.end->pipe_fd[1]);
	if ((builtin = msh_run_builtin(this.end->this->binary)))
		this.end->ret = builtin((const char **)this.end->this->args);
	else
	{
		if (execve(this.this_path, this.end->this->args,
			this.shell->env) == -1)
			ft_dprintf(2, "Trash: permission denied: %s\n",
				this.end->this->binary);
	}
	exit(EXIT_FAILURE);
}

int			piped_fork(t_pipeline this, int out)
{
	this.test = NULL;
	pipe(this.end->pipe_fd);
	this.end->pid = fork();
	if (this.end->pid == 0)
		child_process(this);
	else if (this.end->pid < 0)
	{
		ft_dprintf(2, "Trash: unable to fork process: %d\n", this.pid);
		exit(EXIT_FAILURE);
	}
	else
		parent_process(this, out);
	sh_init_termios();
	return (this.status);
}

static void	pipeline_constructor(t_astree *n, t_pipeline *h, char *p)
{
	h->end = get_end(n);
	h->test = NULL;
	h->this_path = NULL;
	h->path = p;
	h->pipefd[0] = 0;
	h->pipefd[1] = 1;
	h->node = n;
	h->shell = sh_singleton();
}

t_astree	*piped_execution(t_astree *node, char *path)
{
	t_pipeline help;

	pipeline_constructor(node, &help, path);
	help.pid = fork();
	if (help.pid == 0)
		make_process(help, 1);
	else
	{
		wait(&help.status);
		restore_io(help.shell);
	}
	return (help.end);
}
