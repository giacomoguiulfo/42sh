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
#include <termios.h>

void	move_right(t_input *data)
{
	if (data->cursor_pos == data->line_size)
		return ;
	if (data->cursor_col + 1 == data->width)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	data->cursor_pos++;
	if (data->clipboard.copy_on == true)
	{
		if (data->clipboard.end < data->cursor_pos)
			data->clipboard.end = data->cursor_pos;
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgetstr("ic", NULL), 1, ft_putchar);
		ft_putchar(data->line_buff[data->cursor_pos]);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
}

void	move_left(t_input *data)
{
	if (data->cursor_pos == 0)
		return ;
	if (data->cursor_col == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, data->width - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	data->cursor_pos--;
	if (data->clipboard.copy_on == true)
	{
		if (data->clipboard.start > data->cursor_pos)
			data->clipboard.start = data->cursor_pos;
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgetstr("ic", NULL), 1, ft_putchar);
		ft_putchar(data->line_buff[data->cursor_pos]);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
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

typedef struct	s_opt_move
{
	char	name[5];
	char	id;
	bool	direction;
	void	(*opt_move)(struct s_input *, bool);
}				t_opt_move;

t_opt_move	g_opt_move[] = {
	{"left", 'D', false, &move_word},
	{"right", 'C', true, &move_word},
	{"down", 'B', false, &move_word},
	{"up", 'A', true, &move_word},
};

typedef struct	s_move
{
	char		name[5];
	char		id;
	char		type;
	bool		direction;
	void		(*move)(struct s_input *);
	void		(*history)(struct s_input *, struct s_cmds *, bool);
}				t_move;

t_move		g_move[] = {
	{"right", RIGHT, 'm', true, &move_right, NULL},
	{"left", LEFT, 'm', true, &move_left, NULL},
	{"home", HOME, 'm', true, &move_home, NULL},
	{"end", END, 'm', true, &move_end, NULL},
	{"up", UP, 'h', true, NULL, &history_change},
	{"down", DOWN, 'h', false, NULL, &history_change}
};

typedef	struct	s_edit
{
	char		name[5];
	char		id;
	char		id2;
	int			opt;
	void		(*edit)(t_input *data, t_text *clipboard, int opt);	
}				t_edit;

t_edit		g_edit[] = {
	{"copy", -61, -89, 0, &copy_cut_paste},
	{"copy", -30, -119, 1, &copy_cut_paste},
	{"copy", -30, -85, 2, &copy_cut_paste},
	{"copy", -30, -102, 3, &copy_cut_paste},
};

void	move_cursor(t_input *data, t_cmds *history)
{
	int x;

	if (data->char_buff[2] == '[')
	{
		t_opt_move *check;
		x = -1;
		while (++x < 4)
		{
			check = &g_opt_move[x];
			if (data->char_buff[3] == check->id)
			{
				check->opt_move(data, check->direction);
				break ;
			}
		}
	}
	else if (data->char_buff[0] < 0)
	{
		t_edit *check_edit;

		x = -1;
		while (x < 4)
		{
			check_edit = &g_edit[++x];
			if (data->char_buff[1] == check_edit->id2 || data->char_buff[2] == check_edit->id2)
			{
				check_edit->edit(data, &data->clipboard, check_edit->opt);
				break ;
			}
		}
	}
	/*else if (data->char_buff[0] == -61 && data->char_buff[1] == -89)
	{
		copy_cut_paste(data, &data->clipboard, 0);
	}
	else if (data->char_buff[0] == -30 && data->char_buff[1] == -119)
	{
		copy_cut_paste(data, &data->clipboard, 1);
	}
	else if (data->char_buff[0] == -30 && data->char_buff[2] == -85)
	{
		copy_cut_paste(data, &data->clipboard, 2);
	}
	else if (data->char_buff[0] == -30 && data->char_buff[2] == -102)
	{
		copy_cut_paste(data, &data->clipboard, 3);
	}*/
	else
	{
		t_move *check_m;
		x = -1;
		while (x < 6)
		{
			check_m = &g_move[++x];
			if (data->char_buff[2] == check_m->id)
			{
				if (check_m->type == 'h')
					check_m->history(data, history, check_m->direction);
				else
					check_m->move(data);
				break ;
			}
		}
	}
}
