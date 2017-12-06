/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_instruction	*add_command(t_instruction *vector, t_command *cmd)
{
	t_instruction	*tmp;
	t_command		**cmds;
	int				x;
	int				y;

	if (!vector)
	{
		x = 1;
		tmp = (t_instruction*)ft_memalloc(sizeof(t_instruction));
		tmp->count = 1;
		tmp->commands = (t_command**)ft_memalloc(sizeof(t_command*) * (x + 1));
		tmp->commands[0] = cmd;
		tmp->commands[x] = 0;
		return (tmp);
	}
	x = -1;
	while (vector->commands && vector->commands[++x])
		;
	cmds = (t_command**)ft_memalloc(sizeof(t_command*) * (x + 1 + 1));
	cmds[x + 1] = 0;
	y = -1;
	while (++y < x)
		cmds[y] = vector->commands[y];
	cmds[x] = cmd;
	free(vector->commands);
	vector->commands = cmds;
	vector->count++;
	return (vector);
}

char	**add_string(char **string, char *add)
{
	char	**tmp;
	char	**new_shit;
	int		x;
	int		y;

	if (!string)
	{
		x = 1;
		tmp = (char**)ft_memalloc(sizeof(char*) * (x + 1));
		tmp[x] = 0;
		tmp[0] = add;
		return (tmp);
	}
	x = -1;
	while (string[++x])
		;
	new_shit = (char**)ft_memalloc(sizeof(char*) * (x + 1 + 1));
	new_shit[x + 1] = 0;
	y = -1;
	while (++y < x)
	{
		new_shit[y] = string[y];
	}
	new_shit[x] = add;
	return (new_shit);
}