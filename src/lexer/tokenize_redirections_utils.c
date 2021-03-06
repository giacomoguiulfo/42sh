/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	get_suffix_word(char *instr, t_toke *help, t_tokelist *node)
{
	int len;

	len = 0;
	node->redir_suffix_file = instr + help->x;
	while (ft_isfilename(instr[len + help->x]))
		len++;
	node->redir_suffix_file = ft_hstrndup(instr + help->x, len);
	help->x += len;
	help->x--;
}

static void	get_suffix_quote(char *instr, t_toke *help, t_tokelist *node)
{
	int		len;
	char	quote;

	len = 0;
	quote = instr[help->x];
	node->redir_suffix_file = instr + help->x + 1;
	quote = instr[help->x];
	while (instr[help->x + len] != quote)
		len++;
	node->redir_suffix_file = ft_hstrndup(instr + help->x + 1, len);
}

static bool	ft_isnotfile(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else if (c == ';' || c == '|')
		return (true);
	return (false);
}

bool		get_file(char *instr, t_toke *help, t_tokelist *node)
{
	if (ft_isfilename(instr[help->x]))
	{
		get_suffix_word(instr, help, node);
		return (true);
	}
	else if (ft_isquote(instr[help->x]))
	{
		get_suffix_quote(instr, help, node);
		return (true);
	}
	else if (ft_isnotfile(instr[help->x]))
	{
		return (true);
	}
	return (false);
}
