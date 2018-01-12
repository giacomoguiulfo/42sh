/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	check_redirs(char *instr, t_toke *help)
{
	int x;

	x = -1;
	while (ft_isdigit(instr[help->x + (++x)]))
		;
	if (instr[help->x + x] == '>' || instr[help->x + x] == '<')
	{
		help->x += x;
		return (true);
	}
	return (false);
}

void	tokenize_words(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (instr[help->x] == '&' || ft_isdigit(instr[help->x]))
	{
		if (check_redirs(instr, help))
		{
			tokenize_redirs(instr, help, head);
			return ;
		}
	}
	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = 'w';
	help->start = instr + help->x;
	while (instr[help->x++] != '\0' && ft_isfilename(instr[help->x]))
		;
	help->end = instr + help->x;
	tmp->len = help->end - help->start;
	tmp->content = help->start;
	help->x--;
}
