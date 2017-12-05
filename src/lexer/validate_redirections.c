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
	else if (str[0] == '>')
		return (3);
	else if (str[0] == '<' && str[1] == '<')
		return (2);
	else if (str[0] == '<')
		return (1);
	return (0);
}


bool	check_output_redir(char *instr, int *x)
{
	ft_printf("Lexer: output redir found at %d, %s\n", *x, instr);
	if (check_output_from(instr, *x))
		return (false);
	return (true);
}

bool	check_input_redir(char * instr, int *x)
{
	ft_printf("Lexer: input redir found at %d, %s\n", *x, instr);
	return (true);
}

bool	validate_redirections(char *instr)
{
	int x = -1;
	int redir;

	ft_printf("Inside redirections\n");
	while (instr[++x])
	{
		if (ft_isquote(instr[x]))
			skip_quote(instr, &x, instr[x]);
		else if ((redir = ft_isredir(instr + x)))
		{
			if (redir > 2)
			{
				if (!check_output_redir(instr, &x))
					return (false);
			}
			else
			{
				if (!check_input_redir(instr, &x))
					return (false);
			}
		}
	}
	ft_printf("Lexer: redirections look solid\n");
	return (true);
}
