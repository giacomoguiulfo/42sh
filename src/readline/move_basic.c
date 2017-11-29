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

void	move_right(t_input *data)
{
	if (data->cursor_col + 1 == data->width)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	data->cursor_pos++;
}

void	move_left(t_input *data)
{
	if (data->cursor_col == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, data->width - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	data->cursor_pos--;
}

void	move_home(t_input *data)
{
	size_t row;
	size_t col;

	if (data->cursor_pos == 0)
		return ;
	row = data->cursor_row;
	col = data->prompt_size % data->width;
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_putchar);
	data->cursor_pos = 0;
}

void	move_end(t_input *data)
{
	size_t row;
	size_t col;

	if (data->cursor_pos == data->line_size)
		return ;
	row = data->end_row;
	col = data->end_col;
	while (row-- > 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_putchar);
	data->cursor_pos = data->line_size;
}

void	move_cursor(t_input *data, t_cmds *history)
{
	if (data->char_buff[2] == RIGHT && data->cursor_pos < data->line_size)
	{
		move_right(data);
	}
	else if (data->char_buff[2] == LEFT && data->cursor_pos > 0)
	{
		move_left(data);
	}
	else if (data->char_buff[2] == HOME)
	{
		move_home(data);
	}
	else if (data->char_buff[2] == END)
	{
		move_end(data);
	}
	else if (data->char_buff[2] == UP)
	{
		history_change(data, history, true);
	}
	else if (data->char_buff[2] == DOWN)
	{
		history_change(data, history, false);
	}
	else if (data->char_buff[2] == '[' && data->char_buff[3] == 'D')
	{
		move_word(data, false);
	}
	else if (data->char_buff[2] == '[' && data->char_buff[3] == 'C')
	{
		move_word(data, true);
	}
	else if (data->char_buff[2] == '[' && data->char_buff[3] == 'B')
	{
		move_row(data, true);
	}
	else if (data->char_buff[2] == '[' && data->char_buff[3] == 'A')
	{
		move_row(data, false);
	}
}
