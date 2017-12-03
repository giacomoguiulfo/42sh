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
		if (ft_isalnum(inst[*index]))
			return (true);
	}
	return (false);
}

bool	validate_chains(char *inst)
{
	bool	chain_on;
	int		x;

	x = -1;
	chain_on = false;
	while (inst[++x])
	{
		if (inst[x] == '|' || inst[x] == '&')
		{
			chain_on = true;
			if (inst[x] == '|' && inst[x + 1] == '|')
			{
				x++;
				//ft_printf("Lexer: Found OR\n");
				chain_on = get_close_chain(inst, &x);
			}
			else if (inst[x] == '&' && inst[x + 1] == '&')
			{
				x++;
				//ft_printf("Lexer: Found AND\n");
				chain_on = get_close_chain(inst, &x);
			}
			else if (inst[x] == '|')
			{
				//ft_printf("Lexer: Found PIPE\n");
				chain_on = get_close_chain(inst, &x);
			}
			if (!chain_on)
				return (false);
		}
	}
	return (true);
}
