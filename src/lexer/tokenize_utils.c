/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		ft_iscompletechain(char *str)
{
	if (ft_isdepchain(str))
		return (1);
	else if (str[0] == ';')
		return (1);
	return (0);
}

int		ft_isfilename(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '_' || c == '.' || c == ',' || c == '-' || c == '=' ||
		c == '+' || c == '%' || c == '#' || c == '@' || c == '^' || c == '$' ||
		c == '~' || c == '/' || c == '{' || c == '}' || c == '(' || c == ')' ||
		c == '[' || c == ']' || c == ':' || c == '?' || c == '!' || c == '&' ||
		c == '*')
		return (1);
	return (0);
}

bool	ft_isredirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
