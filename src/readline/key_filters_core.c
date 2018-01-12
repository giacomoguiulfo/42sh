/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_filters_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 07:12:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "history.h"

void	delete_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	else if (master->data->cursor_pos == 0)
		return ;
	trim(master->data);
}

void	print_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	insert(master->data);
	return ;
}

void	home_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_home(master->data);
}

void	end_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_end(master->data);
}

void	tab_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	master->data->char_buff[0] = ' ';
	insert(master->data);
	insert(master->data);
	insert(master->data);
	insert(master->data);
	return ;
}
