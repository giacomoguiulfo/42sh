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

void	ft_fputstr(char *str)
{
	int x;

	x = ft_strlen(str);
	write(1, str, x);
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
	if (data->cursor_col + 1 == config->width)
		my_tputs(MOVEDN);
	else
		my_tputs(MOVERIGHT);
}

void	move_left()
{
	my_tputs(MOVELEFT);
}

void	move_home(t_input *data)
{
	size_t x;
	size_t y;

	if (data->cursor_col == 0)
		y = 1;
	else
		y = 0;
	x = data->cursor_pos;
	while (x > y)
	{
		move_left();
		x--;
	}
	data->cursor_pos = 0;
}

void	move_end(t_terminal *config, t_input *data)
{
	size_t x;

	x = data->cursor_pos;
	while (x < data->line_size)
	{
		move_right(config, data);
		if (data->cursor_col + 1 == config->width)
		{
			data->cursor_col = 0;
			data->cursor_row++;
		}
		else
			data->cursor_col++;
		x++;
	}
	data->cursor_pos = data->line_size;
}

void	clear_line(t_terminal *config, t_input *data)
{
	size_t x;
	size_t y;

	move_end(config, data);
	if (data->cursor_col == 0)
		y = 1;
	else
		y = 0;
	x = data->cursor_pos;
	while (x > y)
	{
		if (x % config->width == 0 && x / config->width > 0)
		{
			my_tputs("dc");
			move_left();
			my_tputs("dc");
		}
		else
		{
			move_left();
			my_tputs("dc");
		}
		x--;
	}
	my_tputs("dc");
	data->cursor_pos = 0;
	data->line_size = 0;
}

void	history_dn(t_terminal *config, t_input *data, t_cmds *history)
{
	clear_line(config, data);
	if (!history->current || !history->current->cmd)
	{
		history->current = history->end;
	}
	else if (history->current->cmd)
	{
		history->current = history->current->prev;
	}
	if (history->current && history->current->cmd)
	{
		ft_printf("%s", history->current->cmd);
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = ft_strlen(history->current->cmd);
		data->cursor_pos = data->line_size;
		ft_strcpy(data->line_buff, history->current->cmd);
	}
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}

void	history_up(t_terminal *config, t_input *data, t_cmds *history)
{
	clear_line(config, data);
	if (!history->current || !history->current->cmd)
	{
		history->current = history;
	}
	else if (history->current->cmd)
	{
		history->current = history->current->next;
	}
	if (history->current && history->current->cmd)
	{
		ft_printf("%s", history->current->cmd);
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = ft_strlen(history->current->cmd);
		data->cursor_pos = data->line_size;
		ft_strcpy(data->line_buff, history->current->cmd);
	}
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}

t_cmds	history_constructor(void)
{
	t_cmds	history;

	history.prev = NULL;
	history.next = NULL;
	history.end = NULL;
	history.cmd = NULL;
	history.current = NULL;
	return (history);
}

void	history_add(t_cmds *head, char *cmd)
{
	if (!head->cmd)
	{
		head->cmd = ft_strdup(cmd);
		return ;
	}
	else if (!head->next)
	{
		head->next = (t_cmds*)ft_memalloc(sizeof(t_cmds));
		head->next->next = NULL;
		head->next->prev = head;
		head->end = head->next;
		head->next->cmd = ft_strdup(cmd);
		return ;
	}
	head->end->next = (t_cmds*)ft_memalloc(sizeof(t_cmds));
	head->end->next->next = NULL;
	head->end->next->prev = head->end;
	head->end->next->cmd = ft_strdup(cmd);
	head->end = head->end->next;
}

void	cleanup_history(t_cmds *head)
{
	t_cmds *tmp;
	t_cmds *prev;
	if (head->cmd)
		free(head->cmd);
	tmp = head->next;
	{
		while (tmp)
		{
			prev = tmp;
			tmp = tmp->next;
			free(prev->cmd);
			free(prev);
		}
	}
}

void	move_cursor(t_terminal *config, t_input *data, t_cmds *history)
{
	if (data->char_buff[2] == RIGHT && data->cursor_pos < data->line_size)
	{
		move_right(config, data);
		data->cursor_pos++;
	}
	else if (data->char_buff[2] == LEFT && data->cursor_pos > 0)
	{
		move_left();
		data->cursor_pos--;
	}
	else if (data->char_buff[2] == HOME)
	{
		move_home(data);
	}
	else if (data->char_buff[2] == END)
	{
		move_end(config, data);
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

void	delete(t_terminal *config, t_input *data)
{
	char	buff[LINE_BUFF_SIZE];
	char	*tmp;
	size_t	old_cursor_pos;

	if (data->cursor_pos == 0)
		return ;
	ft_bzero((void*)buff, LINE_BUFF_SIZE);
	tmp = &data->line_buff[data->cursor_pos - 1];
	*tmp = '\0';
	ft_strcpy(buff, tmp + 1);
	ft_strcpy(data->line_buff + data->cursor_pos, buff);
	old_cursor_pos = data->cursor_pos;
	clear_line(config, data);
	my_tputs("im");
	ft_fputstr(data->line_buff);
	my_tputs("ei");
	data->line_size = ft_strlen(data->line_buff);
	data->cursor_pos = data->line_size;
	while (data->cursor_pos > old_cursor_pos - 1)
	{
		move_left();
		data->cursor_pos--;
	}
}

void	insert(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];

	ft_bzero((void*)buff, LINE_BUFF_SIZE);
	ft_strcpy(buff, data->char_buff);
	ft_strcat(buff, data->line_buff + data->cursor_pos);
	data->line_buff[data->cursor_pos] = '\0';
	ft_strcat(data->line_buff, buff);
	my_tputs("im");
	ft_fputstr(data->char_buff);
	my_tputs("ei");
	data->cursor_pos++;
	data->line_size++;
}

char	*readline(t_terminal *config)
{
	input_constructor(&config->data);
	while ((read(0, config->data.char_buff, 5)) && config->data.char_buff[0] != ENTER)
	{
		get_terminal_meta(config, &config->data);
		if (ft_isprint(config->data.char_buff[0]))
			insert(&config->data);
		else if (config->data.char_buff[0] == DELETE)
			delete(config, &config->data);
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
