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

void		print_tokened_list(t_asttoken **head)
{
	int	x;
	int y;

	x = -1;
	while (head[++x])
	{
		ft_printf("\n----------\n");
		ft_printf("binary: %s\n", head[x]->binary);
		if (head[x]->args)
		{
			y = -1;
			while (head[x]->args[++y])
				ft_printf("args: %s\n", head[x]->args[y]);
		}
		if (head[x]->redirs)
		{
			y = -1;
			while (head[x]->redirs[++y])
			{
				if (head[x]->redirs[y]->redir_suffix_file)
					ft_printf("Redir file: %s\n", head[x]->redirs[y]->redir_suffix_file);
			}
			ft_printf("redirs: %d\n", y);
		}
		ft_printf("redirections: TO DO\n");
		ft_printf("chain: %s\n", head[x]->chain);
	}
	ft_printf("----------\n");
}

t_astree	*parser(t_tokelist *tokens)
{
	t_asttoken	**pre_ast;
	t_astree	*mana;

	pre_ast = synthesize_tokens(tokens);
	print_tokened_list(pre_ast);
	mana = make_tree(pre_ast);
	return (mana);
}
