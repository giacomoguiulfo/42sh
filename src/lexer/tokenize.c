/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

t_instruction	*tokenize_constructor(t_cmd_extractor *help, char *instr)
{
	help->found_bin = false;
	help->start = instr;
	help->end = NULL;
	help->bin_start = NULL;
	help->bin_end = NULL;
	help->arg_start = NULL;
	help->arg_end = NULL;
	ft_bzero((void*)help->buff, MAX_PATH_BIN_SIZE);
	help->x = -1;
	return (NULL);
}

int		is_redir_check(char *str, int index)
{
	while (ft_isdigit(str[++index]))
		;
	if (str[index] == '<' || str[index] == '>')
		return (0);
	return (1);
}

int		ft_isbin(char c, char *str, int index)
{
	if ((c == '"' || c == 39) || (ft_isalpha(c)))
		return (1);
	else if (ft_isdigit(c))
	{
		if (is_redir_check(str, index))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	tokenize(char *instructions)
{
	t_cmd_extractor help;
	t_instruction	*commands;

	ft_putstr("Inside tokenize\n");
	commands = tokenize_constructor(&help, instructions);
	while (instructions[++help.x])
	{
		if (ft_ischain(instructions[help.x]))
		{
			help.end = instructions + help.x;
			command_extractor(commands, help);
			help.start = help.end + 1;
		}
	}
	help.end = instructions + help.x;
	command_extractor(commands, help);
	ft_putstr("Finished tokenize\n");
}