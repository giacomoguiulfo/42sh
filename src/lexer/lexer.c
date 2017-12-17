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
#include "history.h"
#include <stdlib.h>

void		history_add(char *cmd);

bool		validate(char **instr)
{
	int		valid;
	bool	changed;

	valid = 0;
	changed = false;
	while (!valid)
	{
		valid = validate_quotes_chains(instr);
		if (valid == -1)
			return (false);
		if (!valid)
			changed = true;
	}
	if (!validate_chain_bins(*instr))
		return (false);
	if (!validate_redirections(*instr))
		return (false);
	if (changed == true)
		history_add(*instr);
	return (true);
}
			
t_tokelist	*lexer(char **instr)
{
	t_tokelist *abstract;

	if (!validate(instr))
	{
		ft_printf("Lexer: Not a valid command: %s\n", *instr);
		return (NULL);
	}
	abstract = tokenize(*instr);
	return (abstract);
}