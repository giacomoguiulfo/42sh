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

static int	sh_instruction(t_shell *shell)
{
	char	*cmds;
	char	*prompt;

	while (42)
	{
		prompt = msh_put_arrow();
		cmds = readline(prompt);
		ft_putstr("hi\n");
		ft_printf("cmd size: %zu\n", ft_strlen(cmds));
		free(prompt);
		if (!cmds)
			continue ;
		lexer(&cmds);
		free(cmds);
		if (shell->quit == true)
			break ;
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
	// 	sh_reset();
	}
	builtin_exit();
	return (0);
}
