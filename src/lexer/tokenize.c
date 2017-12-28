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
	help->ret = -1;
	head = start_toking();
	return (head);
}

int		check_type(char *instructions, t_toke *help)
{
	int type;

	type = 4;
	if (ft_isfilename(instructions[help->x]))
		type = 0;
	else if (ft_isquote(instructions[help->x]))
		type = 1;
	else if (ft_isredirection(instructions[help->x]))
		type = 2;
	else if (ft_iscompletechain(instructions + help->x))
		type = 3;
	return (type);
}

typedef	struct 	s_test
{
	int			type;
	void		(*tokenizer)(char *, t_toke *, t_tokelist *);
}				t_test;

t_test 		g_dispatch[] = {
	{0, &tokenize_words},
	{1, &tokenize_quotes},
	{2, &tokenize_redirections},
	{3, &tokenize_chain},
	{4, NULL}
};

t_tokelist	*tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	while (++help.x < help.size)
	{
		help.ret = check_type(instructions, &help);
		if (help.ret == 4)
			continue ;
		g_dispatch[help.ret].tokenizer(instructions, &help, head);
	}
	return (head);
}