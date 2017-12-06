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

void	command_extractor(t_instruction *cmds, t_cmd_extractor help)
{
	if (!get_bin(&help))
		return ;
	cmds = add_command(cmds, NULL);
	ft_printf("command count: %zu\n", cmds->count);
	cmds->commands[0]->binary = help.bin_start;
	ft_printf("Found your binary: %s\n", help.bin_start);
}