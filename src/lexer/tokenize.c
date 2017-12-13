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
	help->size = ft_strlen(instr);
	head = start_toking();
	return (head);
}

void		tokenize_this_part(char *instructions, t_toke *help, t_tokelist *head)
{
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

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	while (++help.x < help.size)
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