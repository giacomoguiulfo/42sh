/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:24:57 by giacomo           #+#    #+#             */
/*   Updated: 2018/01/18 10:58:14 by gguiulfo         ###   ########.fr       */
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

static void shell_free(t_shell *shell)
{
	history_cleanup(shell->history);
	ft_sstrdel(&shell->argv);
	if (shell->env)
		ft_sstrdel(&shell->env);
	if (shell->localenv)
		ft_sstrdel(&shell->localenv);
	free(shell);
}

int			builtin_exit(char **av)
{
	t_shell	*shell;
	int		status;

	shell = sh_singleton();
	status = (av[1]) ? ft_atoi(av[1]) : shell->status;
	if (av[1] && av[2])
	{
		SH_ERR2("%s: too many arguments", av[0]);
		return (1);
	}
	shell_free(shell);
	terminal_reset();
	exit(status);
	return (0);
}
