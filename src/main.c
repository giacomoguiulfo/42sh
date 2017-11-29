/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 10:39:25 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static int	sh_readline()
{
	char	*line;
	char	*prompt;
	char	**args;

	prompt = msh_put_arrow();
	line = readline(prompt);
	ft_putchar('\n');
	if (!line)
		return (0);
	args = msh_strsplit(line);
	msh_execute(args);
	free(line);
	free(prompt);
	ft_free_sstr(args);
	return (0);
}

static int	sh_instruction()
{
	while (42)
	{
		sh_readline();
		// lexer
		// parser
	}
	// execute instruction
	return (0);
}

int			main(int ac, char **av)
{
	// g_argv = av;
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
