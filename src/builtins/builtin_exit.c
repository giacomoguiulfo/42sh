/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:24:57 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/28 05:57:15 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sh.h"
#include "../../includes/history.h"
#include "../../includes/readline.h"
#include <unistd.h>
#include <stdlib.h>

static void	terminal_reset(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}

int			builtin_exit(void)
{
	t_shell *shell;
	int		x;

	x = -1;
	shell = sh_singleton();
	history_cleanup(shell->history);
	while (shell->argv[++x] != 0)
		free(shell->argv[x]);
	free(shell->argv[x]);
	x = -1;
	while (shell->env[++x] != 0)
		free(shell->env[x]);
	free(shell->env[x]);
	free(shell->argv);
	free(shell->env);
	free(shell);
	terminal_reset();
	exit(EXIT_SUCCESS);
	ft_printf("Goodbye :]\n");
	return (0);
}
