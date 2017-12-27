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

	ft_printf("Inside extract words\n");
	if (ft_isdigit(instr[help->x]))
	{
		if (check_redirection(instr, help))
			return ;
	}
	ft_printf("Not a redirection\n");
	if (!head->type[0])
		tmp = head;
	else
		tmp = add_toke(head);
	tmp->type[0] = 'w';
	ft_printf("tmp type: %s\n", tmp);
	help->start = instr + help->x;
	ft_printf("before: %s\n", instr + help->x);
	while (instr[help->x++] != '\0' && ft_isfilename(instr[help->x]))
		;
	ft_printf("after: %s\n", instr + help->x);
	help->end = instr + help->x;
	tmp->len = help->end - help->start;
	tmp->content = help->start;
	ft_printf("word content: %s\n", tmp->content);
	ft_printf("left off resume: %s\n", instr + help->x);
}
