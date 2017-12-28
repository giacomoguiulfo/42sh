/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <stdbool.h>

static void	get_window_size(t_input *data)
{
	ioctl(0, TIOCGWINSZ, &data->window_size);
	data->width = data->window_size.ws_col;
	data->height = data->window_size.ws_row;
}

static void	get_cursor_pos(t_input *data)
{
	data->cursor_row = (data->cursor_pos + data->prompt_size) / data->width;
	data->cursor_col = (data->cursor_pos + data->prompt_size) % data->width;
	data->end_row = (data->line_size + data->prompt_size) / data->width;
	data->end_col = (data->line_size + data->prompt_size) % data->width;
}

void		get_terminal_meta(t_input *data)
{
	get_window_size(data);
	get_cursor_pos(data);
}

bool		str_protection(t_input *data, size_t first, size_t second)
{
	size_t overflow;

	overflow = first + second;
	if (overflow > LINE_BUFF_SIZE - 1)
	{
		ft_printf("\nError: buffer length %zu exceeded", LINE_BUFF_SIZE);
		ft_printf(" by %zu characters\n", overflow - LINE_BUFF_SIZE);
		data->clipboard.copy_on = false;
		return (false);
	}
	return (true);
}

void clear_highlights(t_input *data, bool opt)
{
	size_t row;
	size_t col;

	row = data->cursor_row;
	col = data->prompt_size % data->width;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_putstr(data->line_buff);
	if (opt == true)
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
}
