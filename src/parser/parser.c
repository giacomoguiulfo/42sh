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
		y = -1;
		if (head[x]->args)
		{
			while (head[x]->args[++y])
				ft_printf("args: %s\n", head[x]->args[y]);
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
