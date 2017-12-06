/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_command_extractor.c                       :+:      :+:    :+:   */
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
/*
typedef struct	s_cmd_extractor
{
	bool		found_bin;
	char		*start;
	char		*end;
	char		*bin_start;
	char		*bin_end;
	char		buff[MAX_PATH_BIN_SIZE];
	int			x;
}				t_cmd_extractor;

typedef struct			s_command
{
	struct s_redir_in	*in;
	struct s_redir_out	*out;
	struct s_heredoc	*here;
	char				**args;
	char				*binary;
}						t_command;

// Get bin
// get arguments
// get chain status (if any)*/

bool	get_bin(t_cmd_extractor *help)
{
	int x;

	x = -1;
	while (help->start[++x])
	{
		if (ft_isalpha(help->start[x]))
		{
			help->bin_start = help->start + x;
			while (ft_isalpha(help->start[++x]))
				;
			help->start[x] = '\0';
			help->bin_end = help->start + x;
			return (true);
		}
	}
	return (false);
}

t_command *tokenize_command(t_cmd_extractor *help)
{
	t_command *tmp;

	tmp = (t_command*)ft_memalloc(sizeof(t_command));
	tmp->binary = help->bin_start;
	return (tmp);
}

void	command_extractor(t_instruction *cmds, t_cmd_extractor help)
{
	t_command *command;

	if (!get_bin(&help))
		return ;
	command = tokenize_command(&help);
	ft_printf("Your command is %s\n", command->binary);
	add_command(cmds, command);
}