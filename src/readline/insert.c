/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
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

void	clear_insert(t_input *data)
{
	size_t top;

	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	top = data->cursor_row;
	while (top-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

static void	build_buffer(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];

	ft_strcpy(buff, data->char_buff);
	ft_strcat(buff, data->line_buff + data->cursor_pos);
	data->line_buff[data->cursor_pos] = '\0';
	ft_strcat(data->line_buff, buff);
	ft_putstr(data->prompt);
	ft_putstr(data->line_buff);
	data->cursor_pos++;
	data->line_size++;
}

void		gather_position_data(t_input *data)
{
	data->end_col = (data->prompt_size + data->line_size) % data->width;
	data->end_row = (data->prompt_size + data->line_size) / data->width;
	data->cursor_row = (data->prompt_size + data->cursor_pos) / data->width;
	data->cursor_col = (data->prompt_size + data->cursor_pos) % data->width;
}

void		print_end_col_pad(size_t cursor_col)
{
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, cursor_col), 1, ft_putchar);
}

void		insert(t_input *data)
{
	size_t	x;

	if (!str_protection(data, data->line_size, data->line_size + 1))
		return ;
	clear_insert(data);
	build_buffer(data);
	gather_position_data(data);
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
	tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col), 1, ft_putchar);
	x = data->end_row - data->cursor_row;
	while (x-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
}
