/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/ft_sh.h"
#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

void	input_constructor(t_input *data, t_cmds *history)
{

	ft_bzero(data->char_buff, 5);
	ft_bzero(data->line_buff, 4096);
	data->line_size = 0;
	data->cursor_pos = 0;
	data->cursor_col = 0;
	data->cursor_row = 0;
	data->continue_loop = true;
	if (!history)
		history = history_constructor();
}

int		ft_intputchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_isblank(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

int		valid_string(char *str)
{
	int x;

	x = -1;
	while (str[++x])
	{
		if (!(ft_isblank(str[x])))
			return (1);
	}
	return (0);
}

void	get_window_size(t_terminal *config)
{
	ioctl(0, TIOCGWINSZ, &config->window_size);
	config->width = config->window_size.ws_col;
	config->height = config->window_size.ws_row;
}

void	get_cursor_pos(t_terminal *config, t_input *data)
{
	data->cursor_row = (data->cursor_pos + config->prompt_size) / config->width;
	data->cursor_col = (data->cursor_pos + config->prompt_size) % config->width;
	data->end_row = (data->line_size + config->prompt_size) / config->width;
	data->end_col = (data->line_size + config->prompt_size) % config->width;
}

void	get_terminal_meta(t_terminal *config, t_input *data)
{
	get_window_size(config);
	get_cursor_pos(config, data);
}

void	delete(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];
	char	*tmp;

	if (data->cursor_pos == 0)
		return ;
	ft_bzero((void*)buff, ft_strlen(data->line_buff + 1));
	tmp = &data->line_buff[data->cursor_pos - 1];
	*tmp = '\0';
	ft_strcpy(buff, tmp + 1);
	ft_strcpy(data->line_buff + data->cursor_pos - 1, buff);
	tputs(tgetstr("le", NULL), 1, ft_intputchar);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	tputs(tgetstr("im", NULL), 1, ft_intputchar);
	ft_fputstr(buff);
	tputs(tgetstr("ei", NULL), 1, ft_intputchar);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	data->cursor_pos--;
	data->line_size--;
}

void	clear_insert(t_input *data)
{
	size_t top;

	tputs(tgetstr("cr", NULL), 1, ft_intputchar);
	top = data->cursor_row;
	while (top-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
}

void	print_end_col_pad(size_t cursor_col)
{
	tputs(tgetstr("do", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, cursor_col), 1, ft_intputchar);
}

void	gather_position_data(t_terminal *config, t_input *data)
{
	data->end_col = (config->prompt_size + data->line_size) % config->width;
	data->end_row = (config->prompt_size + data->line_size) / config->width;
	data->cursor_row = (config->prompt_size + data->cursor_pos) / config->width;
	data->cursor_col = (config->prompt_size + data->cursor_pos) % config->width;
}

void	build_buffer(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];

	ft_strcpy(buff, data->char_buff);
	ft_strcat(buff, data->line_buff + data->cursor_pos);
	data->line_buff[data->cursor_pos] = '\0';
	ft_strcat(data->line_buff, buff);
}

void	insert(t_terminal *config, t_input *data)
{
	clear_insert(data);
	size_t	x;

	build_buffer(data);
	msh_put_arrow();
	ft_fputstr(data->line_buff);
	data->cursor_pos++;
	data->line_size++;
	gather_position_data(config, data);
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
	tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col), 1, ft_intputchar);
	x = data->end_row - data->cursor_row;
	while (x-- > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	}
}

char	*readline(t_terminal *config)
{
	static t_cmds	*history = NULL;
	t_input			data;

	input_constructor(&data, history);
	while (data.continue_loop == true)
	{
		read(0, &data.char_buff, 5);
		get_terminal_meta(config, &data);
		if (data.char_buff[0] == ENTER)
			data.continue_loop = false;
		else if (ft_isprint(data.char_buff[0]))
			insert(config, &data);
		else if (data.char_buff[0] == DELETE)
			delete(&data);
		else if (data.char_buff[0] == 27)
			move_cursor(config, &data, &data.history);
		ft_bzero((void*)data.char_buff, 5);
	}
	if (!(valid_string(data.line_buff)))
		return (NULL);
	history_add(&data.history, data.line_buff);
	ft_putchar('\n');
	return (ft_strdup(data.line_buff));
}
