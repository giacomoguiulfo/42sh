/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_synthesizer.c                               :+:      :+:    :+:   */
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

bool		ft_isword(char c)
{
	if (c == 'w')
	{
		return (true);
	}
	else if (ft_isquote(c))
	{
		return (true);
	}
	return (false);
}

void		build_argv(t_tokelist *start, t_asttoken *build)
{
	if (start->type[0] == 'w' && !build->binary)
		add_binary(build, start);
	else if (start->type[0] == 'w')
		add_astarg(build, start);
	else if (ft_isquote(start->type[0]))
		add_astarg(build, start);
}

t_asttoken	**get_toke(t_tokelist *s, t_tokelist *e, t_asttoken **b, int c)
{
	if (!b)
		b = add_asttoken(b);
	while (s && s != e)
	{
		if (!b[c])
			b = add_asttoken(b);
		if (ft_isword(s->type[0]))
			build_argv(s, b[c]);
		else if (ft_isredirection(s->type[0]))
			add_redir(b[c], s);
		else if (ft_iscompletechain(s->type))
			add_chain(b[c], s);
		s = s->next;
	}
	if (s && s == e)
	{
		if (!b[c])
			b = add_asttoken(b);
		add_chain(b[c], s);
	}
	return (b);
}

t_asttoken	**synthesize_tokens(t_tokelist *tokens)
{
	t_asttoken	**build;
	t_tokelist	*start;
	t_tokelist	*end;
	int			count;

	build = NULL;
	start = tokens;
	end = tokens;
	count = -1;
	while (end)
	{
		if (ft_iscompletechain(end->type))
		{
			count++;
			build = get_toke(start, end, build, count);
			start = end->next;
		}
		end = end->next;
	}
	if (start)
	{
		count++;
		build = get_toke(start, end, build, count);
	}
	return (build);
}
