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

typedef struct			s_command
{
	struct s_redir_in	*in;
	struct s_redir_out	*out;
	struct s_heredoc	*here;
	char				*args;
}						t_command;

typedef	struct			s_instruction
{
	struct s_command	**commands;
}						t_instruction;

bool	get_close_quote(char *inst, int *index, char quote)
{
	bool	found_delim;

	found_delim = false;
	while (inst[++*index])
	{
		if (inst[*index] == quote)
		{
			found_delim = true;
			break ;
		}
	}
	return (found_delim);
}

bool	validate_basic_quotes(char *inst)
{
	bool	quote_on;
	int		x;

	x = -1;
	quote_on = false;
	while (inst[++x])
	{
		if (inst[x] == 39 || inst[x] == '"')
		{
			quote_on = true;
			ft_printf("~~Found quote %c at index value: %d\n", inst[x], x);
			quote_on = get_close_quote(inst, &x, inst[x]);
			if (!quote_on)
			{
				ft_printf("**Close quote not found\n");
				break ;
			}
			ft_printf("~~Found close quote %c at index value: %d\n", inst[x], x);
		}
	}
	return (quote_on);
}

bool	validate(char *instruction)
{
	if (!instruction)
		return (false);
	validate_basic_quotes(instruction);
	return (true);
}

bool	lexer(char *instruction)
{
	if (!validate(instruction))
		return (false);
	//tokenization
	return (true);
}