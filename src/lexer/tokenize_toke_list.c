/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extract_chains.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	init(t_tokelist *node)
{
	node->content = NULL;
	node->next = NULL;
	node->len = 0;
	node->type[0] = '\0';
	node->type[1] = '\0';
	node->type[2] = '\0';
	node->redir_prefix_fd = -2;
	node->redir_suffix_fd = -2;
	node->redir_suffix_file = NULL;
}

t_tokelist 	*add_toke(t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head)
		return (NULL);
	if (!head->last)
	{
		head->last = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
		head->next = head->last;
		tmp = head->last;
	}
	else
	{
		tmp = head->last;
		tmp->next = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
		tmp = tmp->next;
	}
	head->last = tmp;
	init(tmp);
	return (tmp);
}

t_tokelist	*start_toking(void)
{
	t_tokelist *head;

	head = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
	head->last = NULL;
	init(head);
	return (head);
}
