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
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_tokelist*)ft_hmalloc(sizeof(t_tokelist));
	tmp = tmp->next;
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->len = 0;
	tmp->type[0] = '\0';
	tmp->type[1] = '\0';
	tmp->type[2] = '\0';
	tmp->redir_prefix_fd = -2;
	tmp->redir_suffix_fd = -2;
	tmp->redir_suffix_file = NULL;
	tmp->redir_suffix_len = -2;
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
	head->redir_prefix_fd = -2;
	head->redir_suffix_fd = -2;
	head->redir_suffix_file = NULL;
	head->redir_suffix_len = -1;
	return (head);
}
