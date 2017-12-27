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

bool	ft_isredirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

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
	ft_printf(">type info: %s, %c\n", instructions + help->x, instructions[help->x]);
	if (ft_isfilename(instructions[help->x]))
	{
		ft_printf("Found a file: %s\n", instructions + help->x);
		type = 0;
	}
	else if (ft_isquote(instructions[help->x]))
		type = 1;
	else if (ft_isredirection(instructions[help->x]))
	{
		ft_printf("Found a redirection: %s\n", instructions + help->x);
		type = 2;
	}
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
	{0, &extract_words},
	{1, &extract_quotes},
	{2, &extract_redirections},
	{3, &extract_chain},
	{4, NULL}
};

t_tokelist	*tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	ft_printf("Starting tokenize: %d size\n", help.size);
	ft_printf("Help counter: %d\n", help.x);
	while (++help.x < help.size)
	{
		ft_printf("~~Checking type: %s\n", instructions + help.x);
		help.ret = check_type(instructions, &help);
		if (help.ret == 4)
			continue ;
		if (help.ret == 0)
			ft_printf("extract words, instructs: %s\n", instructions + help.x);
		else if (help.ret == 1)
			ft_printf("extract quotes, instructs: %s\n", instructions + help.x);
		else if (help.ret == 2)
			ft_printf("extract redirection, instructs: %s\n", instructions + help.x);
		else if (help.ret == 3)
			ft_printf("extract chain, instructs: %s\n", instructions + help.x);
		g_dispatch[help.ret].tokenizer(instructions, &help, head);
		ft_printf("After tokenizer\n");
		
	}
	ft_printf("End loop %d\n", help.x);
	return (head);
}