/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
