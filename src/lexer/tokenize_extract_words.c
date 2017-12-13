/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	check_redirection(char *instr, t_toke *help)
{
	int x;
	int y;

	x = help->x;
	y = 0;
	while (instr[++y + x] && ft_isdigit(instr[y + x]))
		;
	if (instr[y + x] == '>')
	{
		help->x += y - 1;
		return (true);
	}
	return (false);
}

void	extract_words(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	if (ft_isdigit(instr[help->x]))
	{
		if (check_redirection(instr, help))
			return ;
	}
	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = 'w';
	help->start = instr + help->x;
	ft_printf("---------->before: help->x value: %d, strlen: %d\n", help->x, ft_strlen(instr));
	while (instr[++help->x] != '\0' && ft_isfilename(instr[help->x]))
		;
	ft_printf("---------->after: help->x value: %d, strlen: %d\n", help->x, ft_strlen(instr));
	help->end = instr + help->x;
	tmp->len = help->end - help->start;
	tmp->content = help->start;
}
