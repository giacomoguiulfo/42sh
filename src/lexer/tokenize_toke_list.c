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

t_tokelist *add_toke(t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head)
		return (NULL);
	if (!head->last)
	{
		ft_printf("adding new tokenize member\n");
		head->last = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
		head->next = head->last;
		tmp = head->last;
	}
	else
	{
		ft_printf("Adding another new tokenize member\n");
		tmp = head->last;
		tmp->next = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
		tmp = tmp->next;
	}
	head->last = tmp;
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->len = 0;
	tmp->type[0] = '\0';
	tmp->type[1] = '\0';
	tmp->type[2] = '\0';
	return (tmp);
}

t_tokelist *start_toking(void)
{
	t_tokelist *head;

	head = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
	head->content = NULL;
	head->next = NULL;
	head->len = 0;
	head->type[0] = '\0';
	head->type[1] = '\0';
	head->type[2] = '\0';
	head->last = NULL;
	return (head);
}
