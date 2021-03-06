/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2018/01/18 10:44:59 by gguiulfo         ###   ########.fr       */
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

int		msh_run_prog(char *executable, char **args, char **newenvp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(executable, args, newenvp) == -1)
		{
			ft_dprintf(2, "Trash: permission denied: %s\n", executable);
		}
	}
	else if (pid < 0)
	{
		ft_dprintf(2, "Trash: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
	}
	wait(&status);
	sh_init_termios();
	return (status);
}

void	pre_execution_io(t_shell *shell, t_astree *node, char **set)
{
	setup_io(shell, node->this->redirs);
	*set = NULL;
}

void	execution(t_shell *shell, t_astree *node, char *this_path, char *path)
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
	sh_singleton()->status = node->ret;
}

void	recursive_execute(t_shell *shell, t_astree *node, char *path)
{
	char	*this_path;

	pre_execution_io(shell, node, &this_path);
	if (node->this->binary && node->type && node->type[0] == '|'
		&& node->type[1] != '|')
		node = piped_execution(node, path);
	else
	{
		if (node->this->binary)
			execution(shell, node, this_path, path);
		restore_io(shell);
	}
	if (node->left && node->type &&
		node->type[0] == '&' && node->ret < 1)
		recursive_execute(shell, node->left, path);
	else if (node->left && node->type && node->type[0] == '|'
		&& node->type[1] == '|' && node->ret > 0)
		recursive_execute(shell, node->left, path);
	if (node->right)
		recursive_execute(shell, node->right, path);
}

void	execute_ast_cmds(t_astree *head)
{
	t_astree	*tmp;
	t_shell		*shell;

	shell = sh_singleton();
	tmp = head;
	recursive_execute(shell, tmp, ft_getenv(shell->env, "PATH"));
}
