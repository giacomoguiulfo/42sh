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

void		add_binary(t_asttoken *build, t_tokelist *binary)
{
	build->binary = ft_hstrndup(binary->content, binary->len);
}

void		add_args(t_asttoken *build, t_tokelist *arg)
{
	add_astarg(build, arg);
}

void		add_chain(t_asttoken *build, t_tokelist *arg)
{
	build->chain = arg->content;
}

void		add_redir(t_asttoken *build, t_tokelist *arg)
{
	add_astredir(build, arg);
}

t_asttoken	**start_asttoken()
{
	t_asttoken	**new;

	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) * (1));
	new[0] = NULL;
	return (new);
}

t_asttoken	**add_asttoken(t_asttoken **array)
{
	int			size;
	int			x;
	t_asttoken	**new;

	if (!array)
	{
		size = 0;
		new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) * (size + 1));
	}
	else
	{
		size = -1;
		while (array[++size])
			;
		new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) * (size + 1 + 1));
	}
	new[size + 1] = 0;
	new[size] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[size]->binary = NULL;
	new[size]->args = NULL;
	new[size]->redirs = NULL;
	new[size]->chain = NULL;
	x = -1;
	while (++x < size)
		new[x] = array[x];
	array = new;
	return (new);
}

t_asttoken	**get_token_info(t_tokelist	*start, t_tokelist *end, t_asttoken **build, int count)
{
	t_tokelist *tmp;

	tmp = start;
	if (!build)
		build = add_asttoken(build);
	while (tmp && tmp != end)
	{
		if (!build[count])
			build = add_asttoken(build);
		if (tmp->type[0] == 'w' && !build[count]->binary)
			add_binary(build[count], tmp);
		else if (tmp->type[0] == 'w')
			add_astarg(build[count], tmp);
		else if (ft_isredirection(tmp->type[0]))
			add_redir(build[count], tmp);
		else if (ft_iscompletechain(tmp->type))
			add_chain(build[count], tmp);
		tmp = tmp->next;
	}
	if (tmp && (!tmp->type[0] || ft_iscompletechain(tmp->type)))
	{
		if (!build[count])
			build = add_asttoken(build);
		add_chain(build[count], tmp);
	}
	return (build);
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
			build = get_token_info(start, end, build, count);
			start = end->next;
		}
		end = end->next;
	}
	if (start)
	{
		count++;
		build = get_token_info(start, end, build, count);
	}
	return (build);
}
