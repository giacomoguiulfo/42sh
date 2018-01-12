/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/12 14:26:29 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "history.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "execute.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static bool	check_quit(t_shell *shell, char *cmds)
{
	if (shell->quit == true)
	{
		if (cmds)
			free(cmds);
		return (true);
	}
	return (false);
}

static int	pre_processor(t_helper *assist, t_shell *shell)
{
	free(assist->prompt);
	history_reset(shell->history);
	if (check_quit(shell, assist->cmds))
		return (-1);
	else if (!assist->cmds)
		return (0);
	history_add(assist->cmds);
	return (1);
}

static int	processor(t_helper *assist)
{
	if ((assist->tokenized = lexer(&assist->cmds)))
	{
		assist->palm = parser(assist->tokenized);
		if (!assist->palm)
		{
			free(assist->cmds);
			return (0);
		}
		execute_ast_cmds(assist->palm);
	}
	free(assist->cmds);
	return (1);
}

static int	sh_instruction(t_shell *shell)
{
	t_helper	assist;

	while (42)
	{
		assist.prompt = msh_put_arrow();
		assist.cmds = readline(assist.prompt);
		if ((assist.ret = pre_processor(&assist, shell)) == -1)
			break ;
		else if (assist.ret == 0)
			continue ;
		if (!(assist.ret = processor(&assist)))
			continue ;
		break ;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_shell			*shell;
	static t_cmds	history;

	g_argv = av;
	if (sh_init(ac, av, &history))
		return (0);
	shell = sh_singleton();
	while (42)
	{
		sh_instruction(shell);
		ft_heap_clear();
		if (shell->quit == true)
			break ;
	}
	builtin_exit();
	return (0);
}
