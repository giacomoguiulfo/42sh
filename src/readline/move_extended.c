/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

void	move_word(t_input *data, bool direction)
{
	data->width = data->width + 1 - 1;
	if (direction == true)
		ft_putstr("\nmoving right\n");
	else
		ft_putstr("\nmoving left\n");
}

void	move_row(t_input *data, bool direction)
{
	int new_row;

	data->width = data->width + 1 - 1;
	if (direction == true)
	{
		new_row = data->cursor_pos - data->width;
		if (new_row > -1)
		{
			data->cursor_pos = new_row;
			tputs(tgetstr("up", NULL), 1, ft_putchar);
		}
	}
	else
	{
		new_row = data->cursor_pos + data->width;
		if (new_row <= (int)data->line_size)
		{
			data->cursor_pos = new_row;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col),
				1, ft_putchar);
		}
	}
}
