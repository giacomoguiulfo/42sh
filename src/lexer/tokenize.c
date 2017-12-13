/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"

t_tokelist	*tokenize_constructor(t_toke *help, char *instr)
{
	t_tokelist *head;

	help->start = instr;
	help->end = NULL;
	help->x = -1;
	help->state = 0;
	head = start_toking();
	return (head);
}

void		tokenize_this_part(char *instructions, t_toke *help, t_tokelist *head)
{
	ft_printf("tokenizing: %s\n", instructions + help->x);
	ft_printf("x value: %d, strlen: %d\n", help->x, ft_strlen(instructions));
	if (ft_isquote(instructions[help->x]))
		extract_quotes(instructions, help, head);
	else if (ft_isfilename(instructions[help->x]))
		extract_words(instructions, help, head);
	else if (instructions[help->x] == '>' || instructions[help->x] == '<')
		extract_redirections(instructions, help, head);
	else if (ft_iscompletechain(instructions + help->x))
		extract_chain(instructions, help, head);
}

t_tokelist	*tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;
	t_tokelist	*tmp;
	int 		size;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	size = ft_strlen(instructions);
	while (++help.x < size)
	{
		if (ft_isquote(instructions[help.x]) ||
			ft_isfilename(instructions[help.x]) ||
			(instructions[help.x] == '>' || instructions[help.x] == '<') ||
			ft_iscompletechain(instructions + help.x))
		{
			tokenize_this_part(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
		}
	}
	tmp->next = NULL;
	return (head);
}