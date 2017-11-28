/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

void	move_right(t_terminal *config, t_input *data)
{
	data->cursor_pos++;
	if (data->cursor_col + 1 == config->width)
		tputs(tgetstr("do", NULL), 1, ft_intputchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_intputchar);
}

void	move_left(t_input *data)
{
	data->cursor_pos--;
	tputs(tgetstr("le", NULL), 1, ft_intputchar);
}

void	move_home(t_terminal *config, t_input *data)
{
	size_t row;
	size_t col;

	if (data->cursor_pos == 0)
		return ;
	row = data->cursor_row;
	col = config->prompt_size % config->width;
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_intputchar);
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
		tputs(tgetstr("do", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_intputchar);
	data->cursor_pos = data->line_size;
}

void	move_cursor(t_terminal *config, t_input *data, t_cmds *history)
{
	if (data->char_buff[2] == RIGHT && data->cursor_pos < data->line_size)
	{
		move_right(config, data);
	}
	else if (data->char_buff[2] == LEFT && data->cursor_pos > 0)
	{
		move_left(data);
	}
	else if (data->char_buff[2] == HOME)
	{
		move_home(config, data);
	}
	else if (data->char_buff[2] == END)
	{
		move_end(data);
	}
	else if (data->char_buff[2] == UP)
	{
		history_up(config, data, history);
	}
	else if (data->char_buff[2] == DOWN)
	{
		history_dn(config, data, history);
	}
}
