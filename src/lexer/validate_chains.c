/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>

bool	get_close_chain(char *inst, int *index)
{
	while (inst[++*index])
	{
		if (ft_isquote(inst[*index]))
			return (true);
		else if (ft_isalnum(inst[*index]))
			return (true);
	}
	return (false);
}

bool	manage_chain(char *inst, int *x)
{
	bool chain_on;

	chain_on = true;
	if (inst[*x] == '|' && inst[*x + 1] == '|')
	{
		*x = *x + 1;
		chain_on = get_close_chain(inst, x);
	}
	else if (inst[*x] == '&' && inst[*x + 1] == '&')
	{
		*x = *x + 1;
		chain_on = get_close_chain(inst, x);
	}
	else if (inst[*x] == '|')
		chain_on = get_close_chain(inst, x);
	return (chain_on);
}

bool	validate_chains(char *inst)
{
	int		x;

	x = -1;
	while (inst[++x])
	{
		if (ft_isquote(inst[x]))
			skip_quote(inst, &x, inst[x]);
		if (inst[x] == '|' || inst[x] == '&')
		{
			if (!manage_chain(inst, &x))
				return (false);
		}
	}
	return (true);
}
