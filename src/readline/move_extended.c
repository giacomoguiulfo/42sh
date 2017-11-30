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

static void	change_pos(t_input *data, size_t new_pos)
{
	size_t new_col;
	size_t new_row;

	new_col = (new_pos + data->prompt_size) % data->width;
	new_row = (new_pos + data->prompt_size) / data->width;
	if (new_row != data->cursor_row)
	{
		if (new_row > data->cursor_row)
		{
			while (new_row-- > data->cursor_row)
				tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
		else
		{
			while (new_row++ < data->cursor_row)
				tputs(tgetstr("up", NULL), 1, ft_putchar);
		}
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, new_col), 1, ft_putchar);
	data->cursor_pos = new_pos;
}

static void	find_next_word_left(t_input *data)
{
	size_t	next;
	bool	found_space;
	bool	found_char;

	next = data->cursor_pos;
	found_space = false;
	found_char = false;
	while (next > 0)
	{
		if (data->line_buff[next] == ' ')
			found_space = true;
		if (found_space == true && ft_isalnum(data->line_buff[next]))
			found_char = true;
		if (found_space == true && found_char == true && data->line_buff[next] == ' ')
			break ;
		next--;
	}
	if (ft_isalnum(data->line_buff[next]))
		found_char = true;
	if (found_space == true && found_char == true && data->line_buff[next] == ' ')
		change_pos(data, ++next);
	else if (found_space == true && found_char == true)
		change_pos(data, next);
	return ;
}

static void	find_next_word_right(t_input *data)
{
	size_t	next;
	bool	found_space;

	next = data->cursor_pos;
	found_space = false;
	while (data->line_buff[next])
	{
		if (data->line_buff[next] == ' ')
			found_space = true;
		if (found_space == true && ft_isalnum(data->line_buff[next])) // change this to be any non-whitespace char
			return (change_pos(data, next));
		next++;
	}
	return ;
}

void		move_word(t_input *data, bool direction)
{
	if (direction == true && data->cursor_pos == data->line_size)
		return ;
	else if (direction == false && data->cursor_pos == 0)
		return ;
	if (direction == true)
		find_next_word_right(data);
	else
		find_next_word_left(data);
}

void		move_row(t_input *data, bool direction)
{
	int new_row;

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
