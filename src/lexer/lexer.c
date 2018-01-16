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
#include "history.h"
#include "ft_sh.h"
#include "libft.h"
#include <stdlib.h>

int			validate_quotes_chains(char **instr)
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

bool		validate(char **instr)
{
	int		valid;

	valid = 0;
	while (!valid && sh_singleton()->quit == false)
	{
		valid = validate_quotes_chains(instr);
		if (valid == -1)
			return (false);
	}
	if (sh_singleton()->quit == true)
		return ((sh_singleton()->quit = false));
	return (true);
}

t_tokelist	*lexer(char **instr)
{
	t_tokelist *tokenized;

	if (!validate(instr))
		return (NULL);
	tokenized = tokenize(*instr);
	return (tokenized);
}
