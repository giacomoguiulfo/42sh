/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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

int		ft_isquote(char c)
{
	if (c == 39 || c == '"' || c == '`')
		return (1);
	return (0);
}

int		ft_isdepchain(char *c)
{
	if (!c)
		return (0);
	if (c[0] == '|')
		return (1);
	else if (c[0] == '&' && c[1] == '&')
		return (1);
	return (0);
}

void	skip_quote(char *inst, int *x, char quote_type)
{
	while (inst[++*x])
	{
		if (inst[*x] == quote_type)
			break ;
	}
}

bool	get_close_chain(char *inst, int index)
{
	while (inst[++index])
	{
		if (ft_isquote(inst[index]))
			return (true);
		else if (ft_isalnum(inst[index]))
			return (true);
	}
	return (false);
}

void	quote_prompt(char **instr, char *prompt)
{
	char	*new_instr;
	char	*tmp;

	new_instr = readline(prompt);
	if (!new_instr)
		return ;
	ft_asprintf(&tmp, "%s\n%s", *instr, new_instr);
	free((*instr));
	free(new_instr);
	*instr = ft_strdup(tmp);
	free(tmp);
}
