/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/25 18:23:21 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"

bool		ft_issub(char c)
{
	if (ft_isalpha(c))
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}

void		check_for_sub(char *find)
{
	char	**env;
	char	*check;
	char	*equal_sign;
	int 	x;
	int		y;

	env = (sh_singleton())->env;
	if ((check = ft_strchr(find, '$')))
	{
		check++;
		x = -1;
		while (ft_issub(check[++x]))
			;
		ft_printf("$$$\n");
		ft_printf("-->%d: %s\n", x, check);
		ft_dprintf(2, "len: %d\n", x);
		y = -1;
		while (env[++y])
		{
			if ((equal_sign = ft_strchr(env[y], '=')))
			{
				equal_sign++;
				if ((ft_strncmp(env[y], check, x)) == 0)
					ft_printf("~~Match is complete!!!!!!!\n");
			}
		}
	}
}

void		substitution_requests(t_asttoken **pre_ast)
{
	int x;
	int y;

	x = -1;
	while (pre_ast[++x])
	{
		ft_printf("x: %d\n", x);
		if (pre_ast[x]->args[0])
		{
			check_for_sub(pre_ast[x]->binary);
			y = -1;
			while (pre_ast[x]->args[++y])
			{
				ft_printf("Args found: %s\n", pre_ast[x]->args[y]);
				check_for_sub(pre_ast[x]->args[y]); // don't forget to check the binary of the struct too
			}
		}
	}
}

t_astree	*parser(t_tokelist *tokens)
{
	t_asttoken	**pre_ast;
	t_astree	*mana;

	pre_ast = synthesize_tokens(tokens);
	mana = make_tree(pre_ast);
	substitution_requests(pre_ast);
	return (mana);
}
