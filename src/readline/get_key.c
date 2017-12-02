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

void	home_key(struct s_klist *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_home(master->data);
}

void	end_key(struct s_klist *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_end(master->data);
}

void	delete_key(struct s_klist *master)
{
	trim(master->data);
}

void	edit_key(struct s_klist *master)
{
	if (master->data->char_buff[0] == -30 && master->data->char_buff[1] == -119) //x
		copy_cut_paste(master->data, &master->data->clipboard, 1);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -102) //v
		copy_cut_paste(master->data, &master->data->clipboard, 3);
	else if (master->data->char_buff[0] == -61 && master->data->char_buff[1] == -89) //c
		copy_cut_paste(master->data, &master->data->clipboard, 0);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -85) //b
		copy_cut_paste(master->data, &master->data->clipboard, 2);
}

t_key		g_key[] = {
	{"print", 0, &print_key},
	{"enter", ENTER, &enter_key},
	{"opt-move", '[', &opt_move_key},
	{"move left", LEFT, &move_key},
	{"move right", RIGHT, &move_key},
	{"move up", UP, &move_key},
	{"move down", DOWN, &move_key},
	{"move home", HOME, &home_key},
	{"move end", END, &end_key},
	{"delete", DELETE, &delete_key},
	{"edit text", 0, &edit_key},
};

void	get_key(t_input *data, t_cmds *history, t_klist *find)
{
	find->data = data;
	find->history = history;
	if (ft_isprint(data->char_buff[0])) // regular chars
		find->this = &g_key[0];
	else if (data->char_buff[0] == DELETE) // delete
		find->this = &g_key[9];
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
	else if (data->char_buff[2] == g_key[7].id) //home key
		find->this = &g_key[7];
	else if (data->char_buff[2] == g_key[8].id) //end key
		find->this = &g_key[8];
	else if (data->char_buff[0] < 0) //edit keys
		find->this = &g_key[10];
}
