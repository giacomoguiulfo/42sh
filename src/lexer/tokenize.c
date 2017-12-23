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

	type = 0;
	if (ft_isfilename(instructions[help->x]))
		type = 1;
	else if (ft_isquote(instructions[help->x]))
		type = 2;
	else if (instructions[help->x] == '>' || instructions[help->x] == '<')
		type = 3;
	else if (ft_iscompletechain(instructions + help->x))
		type = 4;
	return (type);
}

typedef	struct 	s_test
{
	int			type;
	void		(*tokenizer)(char *, t_toke *, t_tokelist *);
}				t_test;

t_test 		g_dispatch[] = {
	{1, &extract_words},
	{2, &extract_quotes},
	{3, &extract_redirections},
	{4, &extract_chain},
	{0, NULL}
};

t_tokelist	*tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;
	t_tokelist	*tmp;
	int			x;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	ft_printf("Starting tokenize\n");
	x = -1;
	while (++help.x < help.size)
	{
		x = -1;
		help.ret = check_type(instructions + help.x, &help);
		if (help.ret == 0)
			continue ;
		while (++x < 5)
		{
			ft_printf("type: %d, instructions: %s\n", g_dispatch[x].type, instructions + help.x);
			if (g_dispatch[x].type == help.ret)
			{
				ft_printf("!!!type: %d bin->%s\n", g_dispatch[x].type, instructions + help.x);
				g_dispatch[x].tokenizer(instructions, &help, head);
				ft_printf("Crashing inside tokenize\n");
				break ;
			}
		}
		/*if (ft_isquote(instructions[help.x]) ||
			ft_isfilename(instructions[help.x]) ||
			(instructions[help.x] == '>' || instructions[help.x] == '<') ||
			ft_iscompletechain(instructions + help.x))
		{
			tokenize_this_part(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
		}*/
	}
	tmp->next = NULL;
	return (head);
}