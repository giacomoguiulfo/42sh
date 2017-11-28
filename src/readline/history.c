/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_sh.h"

void	history_constructor(t_cmds *history)
{
	history->init = true;
	history->prev = NULL;
	history->next = NULL;
	history->end = NULL;
	history->cmd = NULL;
	history->current = NULL;
}

void		cleanup_history(t_cmds *head)
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
	free(head);
}

static void	history_print(t_input *data, t_cmds *history)
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
		if (direction == true)
			history->current = history;
		else
			return ;
	}
	else if (history->current->cmd)
	{
		if (direction == true)
			history->current = history->current->next;
		else
			history->current = history->current->prev;
	}
	if (history->current && history->current->cmd)
	{
		history_print(data, history);	
	}
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}

void		history_add(t_cmds *head, char *cmd)
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
