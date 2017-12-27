/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_extract_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	extract_quotes(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	ft_printf("Inside extract quotes %s\n", instr + help->x);
	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = instr[help->x];
	help->start = instr + help->x;
	while (instr[++help->x] && instr[help->x] != tmp->type[0])
		;
	help->end = instr + help->x;
	tmp->len = (help->end - 1) - (help->start);
	tmp->content = help->start + 1;
	ft_printf("Left extract quotes\n");
}
