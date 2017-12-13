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
	build->chain = arg;
}

void		add_redir(t_asttoken *build, t_tokelist *arg)
{
	add_astredir(build, arg);
}

t_asttoken	**synthesize_tokens(t_tokelist *tokens)
{
	t_tokelist	*tmp;
	t_asttoken	**build;
	int			count;

	tmp = tokens;
	build = start_asttoken();
	count = 0;
	while (tmp)
	{
		if (tmp->type[0] == 'w' || ft_isquote(tmp->type[0]))
		{
			if (!build[count])
				build = add_asttoken(build);
			if (!build[count]->binary)
				add_binary(build[count], tmp);
			else
				add_args(build[count], tmp);
		}
		else if (tmp->type[0] == '>' || tmp->type[0] == '<')
			add_astredir(build[count], tmp);
		else if (ft_iscompletechain(tmp->type))
		{
			add_chain(build[count], tmp);
			count++;
		}
		tmp = tmp->next;
	}
	return (build);
}
