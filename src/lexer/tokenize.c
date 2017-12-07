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
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

typedef struct			s_toke
{
	char				*start;
	char				*end;
	char				quote_type;
	int					x;
	int					state;
}						t_toke;

typedef struct			s_tokelist
{
	void				*content;
	size_t				len;
	char				type;
	struct s_tokelist	*next;
}						t_tokelist;

void	ft_putnstr(char *str, size_t len)
{
	write(1, str, len);
}

t_tokelist *start_toking(void)
{
	t_tokelist *head;

	head = (t_tokelist*)ft_memalloc(sizeof(t_tokelist));
	head->content = NULL;
	head->next = NULL;
	head->len = 0;
	return (head);
}

void	extract_quotes(char *instr, t_toke *help, t_tokelist *head)
{
	t_tokelist *tmp;

	help->quote_type = instr[help->x];
	if (!head->content)
		tmp = head;
	else
	{
		ft_printf("Inside else statement: %s\n", instr + help->x);
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_tokelist*)ft_memalloc(sizeof(t_tokelist));
		tmp = tmp->next;
		ft_printf("Finished else statement\n");
	}
	help->start = instr + help->x;
	while (instr[++help->x] && instr[help->x] != help->quote_type)
		;
	help->end = instr + help->x;
	tmp->len = (help->end - 1) - (help->start);
	tmp->content = help->start + 1;
	ft_printf("Finished extracting more quotes\n");
}



t_tokelist	*tokenize_constructor(t_toke *help, char *instr)
{
	t_tokelist *head;

	help->start = instr;
	help->end = NULL;
	help->x = -1;
	help->state = 0;
	return ((head = start_toking()));
}

void	tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;
	t_tokelist	*tmp;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	ft_printf("Instructions are: %s\n", instructions);
	while (instructions[++help.x])
	{
		if (ft_isquote(instructions[help.x]))
		{
			ft_printf("Inside ft_isquote: %s\n", instructions + help.x);
			extract_quotes(instructions, &help, head);
			if (tmp->next)
				tmp = tmp->next;
			ft_putnstr(tmp->content, tmp->len);
			ft_printf("\nfinished quotes\n");
		}

	}
	ft_printf("Finished tokenizing\n");
}