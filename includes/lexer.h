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

# define MAX_PATH_BIN_SIZE 8192

bool			lexer(char **cmds);
void			tokenize(char	*instructions);

bool			validate_chain_bins(char *instr);
bool			validate_quotes(char *inst);
bool			validate_redirections(char *instr);
int				validate_chains(char *inst);
int				validate_quotes_chains(char **instr);

bool			check_access(char *binary, char *path);
bool			check_binary(char *binary, char *path, int *x);
bool			check_reg_file(mode_t st_mode);

bool			get_close_chain(char *inst, int index);
bool			try_pwd(char *binary);
char			*get_path(void);
int				ft_ischain(char *c);
int				ft_isquote(char c);
void			skip_quote(char *inst, int *x, char quote_type);
void			quote_prompt(char **instr, char *prompt);

#endif
