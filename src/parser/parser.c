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

typedef struct	s_sub
{
	char		**env;
	char		*env_start;
	char		*env_end;
	char		*find_start;
	char		*find_end;
	int			y;
	int			x;
}				t_sub;

void		check_for_sub(char *find, char this)
{
	t_sub	help;

	help.env = (sh_singleton())->env;
	if ((help.find_start = ft_strchr(find, this)))
	{
		help.find_start++;
		help.x = -1;
		while (ft_issub(help.find_start[++help.x]))
			;
		ft_printf("-->%d: %s\n", help.x, help.find_start);
		ft_dprintf(2, "len: %d\n", help.x);
		help.y = -1;
		while (help.env[++help.y])
		{
			if ((help.env_end = ft_strchr(help.env[help.y], '=')))
			{
				help.env_end++;
				if ((ft_strncmp(help.env[help.y], help.find_start, help.x)) == 0)
					ft_printf("~~Match is complete: %s\n", help.env[help.y]);
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
		if (pre_ast[x]->args[0])
		{
			check_for_sub(pre_ast[x]->binary);
			y = -1;
			while (pre_ast[x]->args[++y])
			{
				check_for_sub(pre_ast[x]->args[y], '$'); // don't forget to check the binary of the struct too
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
