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

static void	get_chain_type(char *instr, t_toke *help, t_tokelist *node)
{
	if (instr[help->x] == '&' && instr[help->x + 1] == '&')
	{
		node->type[0] = '&';
		node->type[1] = '&';
		help->x++;
	}
	else if (instr[help->x] == '|' && instr[help->x + 1] == '|')
	{
		node->type[0] = '|';
		node->type[1] = '|';
		help->x++;
	}
	else if (instr[help->x] == '|')
		node->type[0] = '|';
	else if (instr[help->x] == ';')
		node->type[0] = ';';
}

void		tokenize_chain(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->content = instr + help->x;
	get_chain_type(instr, help, tmp);
}
