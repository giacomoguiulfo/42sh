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

#include "../../includes/readline.h"
#include "../../includes/ft_sh.h"

static void	clear_line(t_input *data)
{
	move_home(data);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	data->cursor_pos = 0;
	data->line_size = 0;
}

t_cmds		*history_constructor(void)
{
	t_cmds	*history;

	history = (t_cmds*)ft_memalloc(sizeof(t_cmds));
	history->prev = NULL;
	history->next = NULL;
	history->end = NULL;
	history->cmd = NULL;
	history->current = NULL;
	return (history);
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

void		history_dn(t_input *data, t_cmds *history)
{
	clear_line(data);
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
		ft_fputstr(history->current->cmd);
		data->line_size = ft_strlen(history->current->cmd);
		data->cursor_pos = data->line_size;
		move_end(data);
		ft_bzero(data->line_buff, data->line_size);
		ft_strcpy(data->line_buff, history->current->cmd);
	}
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}

void		history_up(t_input *data, t_cmds *history)
{
	clear_line(data);
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
		ft_fputstr(history->current->cmd);
		data->line_size = ft_strlen(history->current->cmd);
		data->cursor_pos = data->line_size;
		move_end(data);
		ft_bzero(data->line_buff, data->line_size);
		ft_strcpy(data->line_buff, history->current->cmd);
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
