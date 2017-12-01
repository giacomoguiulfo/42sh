/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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

void	opt_move(t_input *data)
{
	t_opt_move *check;
	int x;

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

void	edit_text(t_input *data, t_text *clipboard)
{
	t_edit *check_edit;
	int x;

	x = -1;
	while (++x < 4)
	{
		check_edit = &g_edit[x];
		if (data->char_buff[1] == check_edit->id2 ||
			data->char_buff[2] == check_edit->id2)
		{
			check_edit->edit(data, clipboard, check_edit->opt);
			break ;
		}
	}
}

void	move(t_input *data, t_cmds *history)
{
	t_move	*check_m;
	int		x;

	x = -1;
	while (++x < 6)
	{
		check_m = &g_move[x];
		if (data->char_buff[2] == check_m->id)
		{
			if (check_m->type == 'h' && data->clipboard.copy_on == false)
				check_m->history(data, history, check_m->direction);
			else
				check_m->move(data);
			break ;
		}
	}
}

void	move_cursor(t_input *data, t_cmds *history)
{
	if (data->char_buff[2] == LEFT || data->char_buff[2] == RIGHT)
		move(data, history);
	else if (data->clipboard.copy_on == false)
		move(data, history);
	else if (data->char_buff[2] == '[' && data->clipboard.copy_on == false)
		opt_move(data);
	else if (data->char_buff[0] < 0)
		edit_text(data, &data->clipboard);
}