/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_filters_logistics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 07:12:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "history.h"

void	opt_move_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	if (master->data->char_buff[3] == 'D')
		move_word(master->data, false);
	else if (master->data->char_buff[3] == 'C')
		move_word(master->data, true);
	else if (master->data->char_buff[3] == 'B')
		move_row(master->data, false);
	else if (master->data->char_buff[3] == 'A')
		move_row(master->data, true);
}

void	move_key(struct s_keychain *master)
{
	if (master->data->char_buff[2] == KEY_LEFT)
		move_left(master->data);
	else if (master->data->char_buff[2] == KEY_RIGHT)
		move_right(master->data);
	if (master->data->clipboard.copy_on == false)
	{
		if (master->data->char_buff[2] == KEY_UP)
			history_change(master->data, master->history, true);
		else if (master->data->char_buff[2] == KEY_DOWN)
			history_change(master->data, master->history, false);
	}
}

void	ctrl_c_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		start_stop_highlight(master->data, &master->data->clipboard);
	ft_bzero((void*)master->data->line_buff, LINE_BUFF_SIZE);
	ft_putchar('\n');
	ft_putstr(master->data->prompt);
	master->data->cursor_pos = 0;
	master->data->line_size = 0;
	master->data->clipboard.copy_on = false;
}

void	edit_key(struct s_keychain *master)
{
	if (master->data->char_buff[0] == -30 && master->data->char_buff[1] == -119)
		copy_cut_paste(master->data, &master->data->clipboard, 1);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -102)
		copy_cut_paste(master->data, &master->data->clipboard, 3);
	else if (master->data->char_buff[0] == -61 && master->data->char_buff[1] == -89)
		copy_cut_paste(master->data, &master->data->clipboard, 0);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -85)
		copy_cut_paste(master->data, &master->data->clipboard, 2);
}
