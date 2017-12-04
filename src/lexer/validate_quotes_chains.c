/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes_chains.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"

int		validate_quotes_chains(char **instr)
{
	int valid;

	valid = 0;
	if (!validate_quotes(*instr))
	{
		quote_prompt(instr, "quotes> ");
		return (valid);
	}
	else if ((valid = validate_chains(*instr)) == 0)
	{
		quote_prompt(instr, "chain> ");
		return (valid);
	}
	return (valid);
}
