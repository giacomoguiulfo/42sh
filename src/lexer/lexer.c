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

int		ft_isredir(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (4);
	else if (str[0] == '<' && str[1] == '<')
		return (3);
	else if (str[0] == '>')
		return (2);
	else if (str[0] == '<')
		return (1);
	return (0);
}



bool	validate_redirections(char *instr)
{
	int x = -1;
	int redir;
	while (instr[++x])
	{
		if (ft_isquote(instr[x]))
			skip_quote(instr, &x, instr[x]);
		else if ((redir = ft_isredir(instr + x)))
		{
			ft_printf("Lexer: found redirection %c at %s\n", instr[x], instr + x);
		}
	}
	return (true);
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
	ft_printf("Valid commands: %s\n", *instr);
	//tokenization
	return (true);
}