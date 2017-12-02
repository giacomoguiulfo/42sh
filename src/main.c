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

static int	sh_instruction()
{
	char	*cmds;
	char	*prompt;

	while (42)
	{
		prompt = msh_put_arrow();
		cmds = readline(prompt);
		free(prompt);
		if (!cmds)
			continue ;
		if (lexer(cmds))
			ft_printf("Valid commands: %s\n", cmds);
		// parser
		// msh_execute(cmds);
		free(cmds);
		//ft_free_sstr(cmds);
	}
	// execute instruction
	return (0);
}

int			main(int ac, char **av)
{
	g_argv = av;
	if (sh_init(ac, av))
		return (0);
	while (42)
	{
		sh_instruction();
	// 	sh_reset();
	}
	builtin_exit();
	return (0);
}
