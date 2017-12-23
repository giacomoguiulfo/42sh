/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/16 18:54:41 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "history.h"
#include "libft.h"
#include "lexer.h"
#include "execute.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	history_add();

static bool check_quit(t_shell *shell, char *cmds)
{
	if (shell->quit == true)
	{
		if (cmds)
			free(cmds);
		return (true);
	}
	return (false);
}

static int	sh_instruction(t_shell *shell)
{
	char			*cmds;
	char			*prompt;
	t_tokelist		*abstract;

	while (42)
	{
		prompt = msh_put_arrow();
		cmds = readline(prompt);
		free(prompt);
		if (check_quit(shell, cmds))
			break ;
		else if (!cmds)
			continue ;
		history_add(cmds);
		abstract = lexer(&cmds);
		if (abstract)
		{
			parser(abstract);
		}
		free(cmds);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_shell 		*shell;
	static t_cmds	history;

	g_argv = av;
	if (sh_init(ac, av, &history))
		return (0);
	shell = sh_singleton();
	while (42)
	{
		sh_instruction(shell);
		if (shell->quit == true)
			break ;
	}
	builtin_exit();
	return (0);
}
