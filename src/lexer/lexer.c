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
#include <stdlib.h>

bool	validate(char *instruction)
{
	if (!instruction)
		return (false);
	else if (!validate_quotes(instruction))
	{
		ft_printf("Lexer: error - validate quotes\n");
		return (false);
	}
	else if (!validate_chains(instruction))
	{
		ft_printf("Lexer: error - validate chains\n");
		return (false);
	}
	else if (!validate_chain_bins(instruction))
	{
		ft_printf("Lexer: error - validate chain bins\n");
		return (false);
	}
	return (true);
}

bool	lexer(char *instruction)
{
	char	*ptr;

	ptr = get_path();
	if (!validate(instruction))
		return (false);
	//tokenization
	return (true);
}