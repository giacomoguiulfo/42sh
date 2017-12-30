/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
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

t_strfmap	g_builtins[] =
{
	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"env", &builtin_env},
	{"history", &builtin_history},
	{"local", &builtin_setenv},
	{"setenv", &builtin_setenv},
	{"export", &builtin_setenv},
	{"unset", &builtin_unsetenv},
	{"unsetenv", &builtin_unsetenv},
	{"exit", &builtin_exit},
	{NULL, NULL}
};

typedef int						(t_builtin)(const char *av[]);

t_builtin	*msh_run_builtins(t_asttoken *this)
{
	int i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(g_builtins[i].name, this->binary) == 0)
			return (g_builtins[i].f);
		i++;
	}
	return (NULL);
}

int		msh_run_prog(char *executable, char **args, char **newenvp)
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
	sh_init_termios();
	return (status);
}

void	recursive_execute(t_shell *shell, t_astree *node, char *path)
{
	char	*this_path;
	t_builtin	*foo;

	this_path = NULL;
	setup_io(shell, node->this->redirs);
	check_pipes(node);
	if (node->this->binary)
	{
		foo = msh_run_builtins(node->this);
		if (foo)
			node->ret = foo((const char **)node->this->args);
		else
		{
			if ((this_path = build_bin_path(path, node->this->binary)))
				node->ret = msh_run_prog(this_path,
					node->this->args, shell->env);
		}
	}
	restore_io(shell);
	if (node->left && node->type && node->type[0] == '&' && node->ret < 1)
		recursive_execute(shell, node->left, path);
	else if (node->left && node->type && node->type[0] == '|'
		&& node->type[1] == '|' && node->ret > 0)
		recursive_execute(shell, node->left, path);
	if (node->right && node->right->this)
		recursive_execute(shell, node->right, path);
}

void	execute_ast_cmds(t_astree *head)
{
	t_astree	*tmp;
	t_shell		*shell;

	shell = sh_singleton();
	if (!shell->path)
	{
		ft_printf("Kash: path is unset\n");
		return ;
	}
	tmp = head;
	recursive_execute(shell, tmp, shell->path);
	restore_io(shell);
}
