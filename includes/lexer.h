/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_sh.h"

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

bool	lexer(char **cmds);

bool	validate_quotes(char *inst);
bool	validate_chain_bins(char *instr);
int		validate_chains(char *inst);
int		validate_quotes_chains(char **instr);

bool	check_access(char *binary, char *path);
bool	check_binary(char *binary, char *path, int *x);
bool	check_reg_file(mode_t st_mode);

bool	get_close_chain(char *inst, int index);
bool	try_pwd(char *binary);
char	*get_path(void);
int		ft_ischain(char c);
int		ft_isquote(char c);
void	skip_quote(char *inst, int *x, char quote_type);
void	quote_prompt(char **instr, char *prompt);

#endif
