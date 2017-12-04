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

bool	manage_chain(char *inst, int *x)
{
	bool chain_on;

	chain_on = true;
	if (inst[*x] == '|' && inst[*x + 1] == '|')
	{
		*x = *x + 1;
		chain_on = get_close_chain(inst, *x);
	}
	else if (inst[*x] == '&' && inst[*x + 1] == '&')
	{
		*x = *x + 1;
		chain_on = get_close_chain(inst, *x);
	}
	else if (inst[*x] == '|')
		chain_on = get_close_chain(inst, *x);
	return (chain_on);
}

void	check_quotes(char *inst, int *x, int *state)
{
		*state = 1;
		skip_quote(inst, x, inst[*x]);
}

void	check_chain(char *inst, int *x, int *state)
{
	if (*state == 0)
	{
		*state = -1;
		return ;
	}
	else if (*state > 0)
	{
		if (!manage_chain(inst, x))
			*state = 0;
	}
}

int		validate_chains(char *inst)
{
	int		state;
	int		x;

	x = -1;
	state = 0;
	while (inst[++x])
	{
		if (ft_isalnum(inst[x]))
			state = 1;
		else if (ft_isquote(inst[x]))
			check_quotes(inst, &x, &state);
		else if (ft_ischain(inst[x]))
		{
			check_chain(inst, &x, &state);
			if (state < 1)
				break ;
			state = 0;
		}
	}
	if (state == -1)
		ft_printf("Lexer: parse error near %c\n", inst[x]);
	return (state);
}