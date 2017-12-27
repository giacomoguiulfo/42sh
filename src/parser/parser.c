/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"

void		ft_putnstr(char *str, size_t len)
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
		/*if (tmp->type[0] == '>' || tmp->type[0] == '<')
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
		}*/
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

t_astree	*parser(t_tokelist *tokens)
{
	t_asttoken	**pre_ast;
	t_astree	*mana;

	print_toke_list(tokens);
	pre_ast = synthesize_tokens(tokens);
	ft_printf("About to make tree\n");
	mana = make_tree(pre_ast);
	ft_printf("Finished with the tree\n");
	return (mana);
}
