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

void	enter_key();

t_key		g_key[] = {
	{"enter", ENTER, &enter_key},
	{"print", 0, &print_key},
};

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

void	get_key(t_input *data, t_cmds *history, t_klist *find)
{
	find->data = data;
	find->history = history;
	if (ft_isprint(data->char_buff[0]))
		find->this = &g_key[1];
	else if (data->char_buff[0] == g_key[0].id)
		find->this = &g_key[0];
}
