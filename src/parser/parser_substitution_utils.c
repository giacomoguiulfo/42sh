/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_substitution_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/25 18:23:21 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"
#include <stdlib.h>

bool		ft_issub(char c)
{
	if (ft_isalpha(c))
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}

char		*get_home(void)
{
	t_shell	*shell;
	int		x;

	shell = sh_singleton();
	x = -1;
	while (shell->env[++x])
	{
		if (ft_strncmp(shell->env[x], "HOME=", 5) == 0)
			return (shell->env[x]);
	}
	return (NULL);
}
