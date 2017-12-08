/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 15:35:31 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
	char	*cmds;
	char	*prompt;

	while (42)
	{
		prompt = msh_put_arrow();
		cmds = readline(prompt);
		free(prompt);
		if (check_quit(shell, cmds))
			break ;
		else if (!cmds)
			continue ;
		lexer(&cmds);
		free(cmds);
	}
	// execute instruction
	return (0);
}

int			main(int ac, char **av)
{
	t_shell *shell;
	g_argv = av;
	if (sh_init(ac, av))
		return (0);
	shell = sh_singleton();
	while (42)
	{
		sh_instruction(shell);
		if (shell->quit == true)
			break ;
	// 	sh_reset();
	}
	builtin_exit();
	return (0);
}
