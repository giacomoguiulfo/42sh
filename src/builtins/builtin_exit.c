/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:24:57 by giacomo           #+#    #+#             */
/*   Updated: 2018/01/11 15:59:16 by gguiulfo         ###   ########.fr       */
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

	shell = sh_singleton();
	history_cleanup(shell->history);
	ft_sstrdel(&shell->argv);
	ft_sstrdel(&shell->env);
	ft_sstrdel(&shell->localenv);
	free(shell);
	terminal_reset();
	exit(EXIT_SUCCESS);
	ft_printf("Goodbye :]\n");
	return (0);
}
