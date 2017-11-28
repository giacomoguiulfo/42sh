/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_sh.h"

static void	clear_line(t_input *data)
{
	size_t row;

	row = data->cursor_row;
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

static void	print(t_input *data, t_cmds *history)
{
	ft_bzero(data->line_buff, data->line_size);
	ft_strcpy(data->line_buff, history->current->cmd);
	ft_putstr(history->current->cmd);
	data->line_size = ft_strlen(history->current->cmd);
	data->cursor_pos = data->line_size;
	gather_position_data(data);
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
}

void		history_change(t_input *data, t_cmds *history, bool direction)
{
	clear_line(data);
	msh_put_arrow();
	data->cursor_pos = 0;
	if (!history->current || !history->current->cmd)
	{
		if (direction == true && history->hit_end == false)
			history->current = history;
		else if (direction == false && history->hit_end == true)
		{
			history->current = history->end;
			history->hit_end = false;
		}
		else
			return ;
	}
	else if (history->current->cmd)
	{
		if (direction == true)
		{
			history->current = history->current->next;
			if (!history->current)
				history->hit_end = true;
		}
		else
			history->current = history->current->prev;
	}
	if (history->current && history->current->cmd)
		print(data, history);	
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}
