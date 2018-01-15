/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/12 15:58:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_sh.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	signal_handler(int signo)
{
	int		status;
	t_shell	*shell;

	status = 0;
	shell = sh_singleton();
	if (signo == SIGINT)
	{
		shell->continue_loop = false;
		write(1, "\n", 1);
		waitpid(-1, &status, WNOHANG);
	}
}

void		sh_init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGQUIT, signal_handler);
}
