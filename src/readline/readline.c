/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 02:21:52 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/ft_sh.h"
#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

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

static void	get_terminal_meta(t_input *data)
{
	get_window_size(data);
	get_cursor_pos(data);
}

static void	input_constructor(t_input *data, t_cmds *history, size_t prompt)
{
	data->prompt_size = prompt;
	ft_bzero(data->char_buff, CHAR_BUFF_SIZE);
	ft_bzero(data->line_buff, LINE_BUFF_SIZE);
	data->line_size = 0;
	data->cursor_pos = 0;
	data->cursor_col = 0;
	data->cursor_row = 0;
	data->continue_loop = true;
	if (history->init == false)
		history_constructor(history);
}

char		*readline(size_t prompt)
{
	static t_cmds	history;
	t_input			data;

	input_constructor(&data, &history, prompt);
	while (data.continue_loop == true)
	{
		if (read(0, &data.char_buff, 5) == -1)
			return (NULL);
		get_terminal_meta(&data);
		if (ft_isprint(data.char_buff[0]))
			insert(&data);
		else if (data.char_buff[0] == DELETE)
			remove(&data); // TODO: change name
		else if (data.char_buff[0] == 27)
			move_cursor(&data, &history);
		else if (data.char_buff[0] == ENTER)
			data.continue_loop = false;
		ft_bzero((void*)data.char_buff, CHAR_BUFF_SIZE);
	}
	if (!(valid_string(data.line_buff)))
		return (NULL);
	history_add(&history, data.line_buff);
	return (ft_strdup(data.line_buff));
}
