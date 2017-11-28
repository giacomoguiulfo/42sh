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

#include "../../includes/readline.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

static void	clear_insert(t_input *data)
{
	size_t top;

	tputs(tgetstr("cr", NULL), 1, ft_intputchar);
	top = data->cursor_row;
	while (top-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
}

static void	print_end_col_pad(size_t cursor_col)
{
	tputs(tgetstr("do", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, cursor_col), 1, ft_intputchar);
}

static void	gather_position_data(t_input *data)
{
	data->end_col = (data->prompt_size + data->line_size) % data->width;
	data->end_row = (data->prompt_size + data->line_size) / data->width;
	data->cursor_row = (data->prompt_size + data->cursor_pos) / data->width;
	data->cursor_col = (data->prompt_size + data->cursor_pos) % data->width;
}

static void	build_buffer(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];

	ft_strcpy(buff, data->char_buff);
	ft_strcat(buff, data->line_buff + data->cursor_pos);
	data->line_buff[data->cursor_pos] = '\0';
	ft_strcat(data->line_buff, buff);
}

void		insert(t_input *data)
{
	clear_insert(data);
	size_t	x;

	build_buffer(data);
	msh_put_arrow();
	ft_fputstr(data->line_buff);
	data->cursor_pos++;
	data->line_size++;
	gather_position_data(data);
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
	tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col), 1, ft_intputchar);
	x = data->end_row - data->cursor_row;
	while (x-- > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	}
}
