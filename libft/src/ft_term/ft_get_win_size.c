/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_win_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:30:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/31 02:00:28 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>

void	ft_get_win_size(int *x, int *y)
{
	struct winsize win;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	if (x)
		*x = win.ws_col;
	if (y)
		*y = win.ws_row;
}
