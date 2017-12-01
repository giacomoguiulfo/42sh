/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 07:12:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	opt_move_key(struct s_klist *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	if (master->data->char_buff[3] == 'D') //left
		move_word(master->data, false);
	else if (master->data->char_buff[3] == 'C') //right
		move_word(master->data, true);
	else if (master->data->char_buff[3] == 'B') //down
		move_row(master->data, false);
	else if (master->data->char_buff[3] == 'A') //up
		move_row(master->data, true);
}

void	move_key(struct s_klist *master)
{
	if (master->data->char_buff[2] == LEFT)
		move_left(master->data);
	else if (master->data->char_buff[2] == RIGHT)
		move_right(master->data);
	else if (master->data->char_buff[2] == UP)
		history_change(master->data, master->history, true);
	else if (master->data->char_buff[2] == DOWN)
		history_change(master->data, master->history, false);
}

void	enter_key(struct s_klist *master)
{
	master->data->continue_loop = false;
	return ;
}

void	print_key(struct s_klist *master)
{
	insert(master->data);
	return ;
}

t_key		g_key[] = {
	{"print", 0, &print_key},
	{"enter", ENTER, &enter_key},
	{"opt-move", '[', &opt_move_key},
	{"move left", LEFT, &move_key},
	{"move right", RIGHT, &move_key},
	{"move up", UP, &move_key},
	{"move down", DOWN, &move_key}
	//{"edit text", 0, &edit_text},
};
/*
t_move		g_move[] = {
	{"right", RIGHT, 'm', true, &move_cursors, NULL},
	{"left", LEFT, 'm', true, &move_cursors, NULL},
	{"home", HOME, 'm', true, &move_home, NULL},
	{"end", END, 'm', true, &move_end, NULL},
	{"up", UP, 'h', true, NULL, &move_cursors},
	{"down", DOWN, 'h', false, NULL, &move_cursors}
};*/

void	get_key(t_input *data, t_cmds *history, t_klist *find)
{
	find->data = data;
	find->history = history;
	//ft_printf("%s\n", data->char_buff + 2);
	if (ft_isprint(data->char_buff[0])) // regular chars
		find->this = &g_key[0];
	else if (data->char_buff[2] == g_key[3].id) //move left
		find->this = &g_key[3];
	else if (data->char_buff[2] == g_key[4].id) //move right
		find->this = &g_key[4];
	else if (data->char_buff[2] == g_key[2].id) //opt-move
		find->this = &g_key[2];
	else if (data->char_buff[2] == g_key[5].id) //move up
		find->this = &g_key[5];
	else if (data->char_buff[2] == g_key[6].id) //move down
		find->this = &g_key[6];
	else if (data->char_buff[0] == g_key[1].id) //enter key
		find->this = &g_key[1];
	//else if (data->char_buff[2] > 0)
	//	find->this = &g_key[4];
}
