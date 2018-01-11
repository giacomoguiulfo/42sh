/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:37:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/16 18:54:41 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	signal_handler(int signo)
{
	int status;

	status = 0;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		waitpid(-1, &status, 0);
	}
}

void		sh_init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
}
