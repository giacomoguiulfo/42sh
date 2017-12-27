/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extract_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	extract_redirections(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = instr[help->x];
	if (instr[help->x + 1] == tmp->type[0])
		tmp->type[1] = instr[help->x + 1];
	tmp->content = instr + help->x;
}
