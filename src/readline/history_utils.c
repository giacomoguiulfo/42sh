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

void	history_constructor(t_cmds *history)
{
	t_shell *shell;

	shell = sh_singleton();
	shell->history = history;
	history->init = true;
	history->prev = NULL;
	history->next = NULL;
	history->end = NULL;
	history->cmd = NULL;
	history->hit_end = false;
}

void	history_cleanup(t_cmds *head)
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
}

void	history_add(t_input *data, t_cmds *head)
{
	tputs(tgoto(tgetstr("se", NULL), 0, data->width - 1), 1, ft_putchar);
	if (!head->cmd)
	{
		head->cmd = ft_strdup(data->line_buff);
		head->end = head;
		return ;
	}
	else if (!head->next)
	{
		head->next = (t_cmds*)ft_memalloc(sizeof(t_cmds));
		head->next->next = NULL;
		head->next->prev = head;
		head->end = head->next;
		head->next->cmd = ft_strdup(data->line_buff);
		return ;
	}
	head->end->next = (t_cmds*)ft_memalloc(sizeof(t_cmds));
	head->end->next->next = NULL;
	head->end->next->prev = head->end;
	head->end->next->cmd = ft_strdup(data->line_buff);
	head->end = head->end->next;
}
