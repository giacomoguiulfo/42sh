/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>

bool	validate(char **instr)
{
	int		valid;

	valid = 0;
	while (!valid)
	{
		valid = validate_quotes_chains(instr);
		if (valid == -1)
			return (false);
	}
	if (!validate_chain_bins(*instr))
		return (false);
	if (!validate_redirections(*instr))
		return (false);
	return (true);
}
			
bool	lexer(char **instr)
{
	if (!validate(instr))
	{
		ft_printf("Lexer: Not a valid command: %s\n", *instr);
		return (false);
	}
	tokenize(*instr);
	return (true);
}