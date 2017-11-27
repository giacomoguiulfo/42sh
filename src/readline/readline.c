/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sh.h"
#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

void	input_constructor(t_input *data)
{
	ft_bzero(data->char_buff, 5);
	ft_bzero(data->line_buff, 4096);
	data->line_size = 0;
	data->cursor_pos = 0;
	data->cursor_col = 0;
	data->cursor_row = 0;
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

void	my_tputs(char *cmd)
{
	int (*to_function)(int);

	to_function = ft_intputchar;
	tputs(tgetstr(cmd, NULL), 1, to_function);
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

void	move_right(t_terminal *config, t_input *data)
{
	data->cursor_pos++;
	if (data->cursor_col + 1 == config->width)
		my_tputs(MOVEDN);
	else
		my_tputs(MOVERIGHT);
}

void	move_left(t_input *data)
{
	data->cursor_pos--;
	my_tputs(MOVELEFT);
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
		my_tputs("up");
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
		my_tputs("do");
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

int		raw_terminal(t_terminal *config)
{
	struct termios change;

	if ((tgetent(NULL, getenv("TERM")) < 1))
		return (0);
	if ((config->name == getenv("xterm-256color")) == 0)
		ft_dprintf(2, "Opps, problem with terminal name\n");
	tcgetattr(0, &change);
	change.c_lflag &= ~(ICANON | ECHO);
	change.c_cc[VMIN] = 1;
	change.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &change);
	get_window_size(config);
	return (1);
}

void	default_terminal(void)
{
	struct termios revert;

	tcgetattr(0, &revert);
	revert.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &revert);
	return ;
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
	my_tputs(MOVELEFT);
	my_tputs("cd");
	my_tputs("sc");
	my_tputs("im");
	ft_fputstr(buff);
	my_tputs("ei");
	my_tputs("rc");
	data->cursor_pos--;
	data->line_size--;
}

void	clear_insert(t_input *data)
{
	size_t top;

	my_tputs("cr");
	top = data->cursor_row;
	while (top-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	my_tputs("cd");
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
	size_t	x;

	clear_insert(data);
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
	input_constructor(&config->data);
	while ((read(0, config->data.char_buff, 5)) && config->data.char_buff[0] != ENTER)
	{
		get_terminal_meta(config, &config->data);
		if (ft_isprint(config->data.char_buff[0]))
			insert(config, &config->data);
		else if (config->data.char_buff[0] == DELETE)
			delete(&config->data);
		else if (config->data.char_buff[0] == 27)
			move_cursor(config, &config->data, &config->data.history);
		ft_bzero((void*)config->data.char_buff, 5);
	}
	if (!(valid_string(config->data.line_buff)))
		return (NULL);
	history_add(&config->data.history, config->data.line_buff);
	ft_putchar('\n');
	return (ft_strdup(config->data.line_buff));
}
