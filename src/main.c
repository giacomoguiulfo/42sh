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
#include "parser.h"
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

static	void print_lexical_chain(t_tokelist *this)
{
	t_tokelist *tmp;

	tmp = this;
	while (tmp)
	{
		ft_printf("print_lexical_chain - tmp token type: %s\n", tmp->type);
		tmp = tmp->next;
	}
}

static int	sh_instruction(t_shell *shell)
{
	char			*cmds;
	char			*prompt;
	t_tokelist		*tokenized;
	t_astree		*palm;

	palm = NULL;
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
		tokenized = lexer(&cmds);
		if (tokenized)
		{
			print_lexical_chain(tokenized);
			palm = parser(tokenized);
			execute_ast_cmds(palm);
		}
		ft_heap_clear();
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
