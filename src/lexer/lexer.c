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

void	quote_prompt(char **instr, char *prompt)
{
	char	*new_instr;
	char	*tmp;

	new_instr = readline(prompt);
	if (!new_instr)
		return ;
	ft_asprintf(&tmp, "%s%s", *instr, new_instr);
	free((*instr));
	free(new_instr);
	*instr = ft_strdup(tmp);
	free(tmp);
}

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
	//validate redirection syntax next!!
	return (true);
}
			
bool	lexer(char **instr)
{
	if (!validate(instr))
	{
		ft_printf("Lexer: Not a valid command: %s\n", *instr);
		return (false);
	}
	ft_printf("Valid commands: %s\n", *instr);
	//tokenization
	return (true);
}