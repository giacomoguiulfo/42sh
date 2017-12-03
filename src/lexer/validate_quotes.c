/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
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

bool	get_close_quote(char *inst, int *index, char quote)
{
	bool	found_delim;

	found_delim = false;
	while (inst[++*index])
	{
		if (inst[*index] == quote)
		{
			found_delim = true;
			break ;
		}
	}
	return (found_delim);
}

bool	validate_quotes(char *inst)
{
	bool	quote_on;
	int		x;

	x = -1;
	quote_on = false;
	while (inst[++x])
	{
		if (inst[x] == 39 || inst[x] == '"' || inst[x] == '`')
		{
			quote_on = true;
			ft_printf("~~Found quote %c at index value: %d\n", inst[x], x);
			quote_on = get_close_quote(inst, &x, inst[x]);
			if (!quote_on)
			{
				ft_printf("**Close quote not found\n");
				return (false);
			}
			ft_printf("~~Found close quote %c at index value: %d\n", inst[x], x);
		}
	}
	return (true);
}
