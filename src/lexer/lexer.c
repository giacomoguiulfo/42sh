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

bool	validate_quotes(char *inst)
{
	bool	quote_on;
	int		x;

	x = -1;
	quote_on = false;
	while (inst[++x])
	{
		if (inst[x] == 39 || inst[x] == '"' || inst[x] == '`')
		{
			quote_on = true;
			ft_printf("~~Found quote %c at index value: %d\n", inst[x], x);
			quote_on = get_close_quote(inst, &x, inst[x]);
			if (!quote_on)
			{
				ft_printf("**Close quote not found\n");
				return (false);
			}
			ft_printf("~~Found close quote %c at index value: %d\n", inst[x], x);
		}
	}
	return (true);
}

bool	get_close_chain(char *inst, int *index)
{
	while (inst[++*index])
	{
		if (ft_isalnum(inst[*index]))
		{
			ft_printf("Lexer: found alpha numeric char %c for chain at index %d\n", inst[*index], *index);
			return (true);
		}
	}
	ft_printf("Lexer: no alpha numeric found for pipe\n");
	return (false);
}

bool	validate_chains(char *inst)
{
	bool	chain_on;
	int		x;

	x = -1;
	chain_on = false;
	while (inst[++x])
	{
		if (inst[x] == '|' || inst[x] == '&')
		{
			chain_on = true;
			if (inst[x] == '|' && inst[x + 1] == '|')
			{
				x++;
				ft_printf("Lexer: Found OR\n");
				chain_on = get_close_chain(inst, &x);
			}
			else if (inst[x] == '&' && inst[x + 1] == '&')
			{
				x++;
				ft_printf("Lexer: Found AND\n");
				chain_on = get_close_chain(inst, &x);
			}
			else if (inst[x] == '|')
			{
				ft_printf("Lexer: Found PIPE\n");
				chain_on = get_close_chain(inst, &x);
			}
			if (!chain_on)
				return (false);
		}
	}
	return (true);
}

bool	validate(char *instruction)
{
	if (!instruction)
		return (false);
	else if (!validate_quotes(instruction))
	{
		ft_printf("Lexer: Missing basic close quote\n");
		return (false);
	}
	else if (!validate_chains(instruction))
	{
		ft_printf("Lexer: Missing chain\n");
		return (false);
	}
	return (true);
}

bool	lexer(char *instruction)
{
	if (!validate(instruction))
		return (false);
	//tokenization
	return (true);
}