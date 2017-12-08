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

void	ft_putnstr(char *str, size_t len)
{
	write(1, str, len);
}

void		print_toke_list(t_tokelist *head)
{
	t_tokelist *tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("\n----------\n");
		ft_printf("type: %s\n", tmp->type);
		if (tmp->type[0] == '>' || tmp->type[0] == '<')
		{
			if (tmp->redir_suffix_fd != -2)
				ft_printf("Suffix_fd is %d\n", tmp->redir_suffix_fd);
			else if (tmp->redir_suffix_file)
			{
				ft_printf("Suffix file is: ");
				ft_putnstr(tmp->redir_suffix_file, tmp->redir_suffix_len);
				ft_putchar('\n');
			}
			else if (tmp->redir_prefix_fd != -2)
				ft_printf("Prefix_fd is %d\n", tmp->redir_prefix_fd);
		}
		if (ft_isquote(tmp->type[0]))
		{
			ft_printf("Quote text: ");
			ft_putnstr(tmp->content, tmp->len);
			ft_putchar('\n');
		}
		else if (tmp->type[0] == 'w')
		{
			ft_printf("Word text: ");
			ft_putnstr(tmp->content, tmp->len);
			ft_putchar('\n');
		}
		ft_printf("---------->\n");
		tmp = tmp->next;
	}
}

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

void	tokenize_this_part(char *instructions, t_toke *help, t_tokelist *head)
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

void	tokenize(char *instructions)
{
	t_toke 		help;
	t_tokelist	*head;
	t_tokelist	*tmp;

	head = NULL;
	head = tokenize_constructor(&help, instructions);
	tmp = head;
	while (instructions[++help.x])
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
	print_toke_list(head);
	ft_heap_clear();
}