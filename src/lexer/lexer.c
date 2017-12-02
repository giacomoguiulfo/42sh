/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
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

typedef	struct			s_heredoc
{
	char				*delim;
	char				*content;
}						t_heredoc;

typedef struct			s_redir_out
{
	char				**output_files;
	int					*output_fds;
	int					*output_fd_count;	
}						t_redir_out;

typedef struct			s_redir_in
{
	char				**input_files;
	int					*input_fds;
	int					input_fd_count;
}						t_redir_in;

typedef struct			s_cmds
{
	struct s_redir_in	*in;
	struct s_redir_out	*out;
	struct s_heredoc	*here;
	char				*args;
}						t_cmds;

typedef	struct			s_instructions
{
	struct s_cmds		*instructions;
}						t_instructions;

bool	lexer(char *instruction)
{
	char	**split;
	int		index;

	index = -1;
	split = ft_strsplit(instruction, ' ');
	if (!validation(split))
		return (false);
	//tokenization
	ft_sstrputs(split);
	while (split[++index])
		ft_sstrdel(split, index);
	free(split);
	return (true);
}