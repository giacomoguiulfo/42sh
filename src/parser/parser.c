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

t_astree	*parser(t_tokelist *tokens)
{
	t_asttoken	**pre_ast;
	t_astree	*mana;

	pre_ast = synthesize_tokens(tokens);
	mana = make_tree(pre_ast);
	substitution_requests(pre_ast);
	return (mana);
}
