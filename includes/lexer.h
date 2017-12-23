/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/16 20:03:12 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_sh.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>

# define MAX_PATH_BIN_SIZE 8192

typedef struct			s_toke
{
	char				*start;
	char				*end;
	char				quote_type;
	int					x;
	int					state;
	int					size;
}						t_toke;

//tokenize
t_tokelist		*tokenize(char	*instructions);

void			extract_chain(char *instr, t_toke *help, t_tokelist *head);
void			extract_redirections(char *instr, t_toke *help, t_tokelist *head);
void			extract_words(char *instr, t_toke *help, t_tokelist *head);
void			extract_quotes(char *instr, t_toke *help, t_tokelist *head);

//helpers
int				ft_iscompletechain(char *str);
int				ft_isfilename(char c);

//utils
t_tokelist 		*add_toke(t_tokelist *head);
t_tokelist 		*start_toking(void);


//validate
bool			validate_chain_bins(char *instr);
bool			validate_quotes(char *inst);
bool			validate_redirections(char *instr);
int				validate_chains(char *inst);
int				validate_quotes_chains(char **instr);

//utils
bool			check_access(char *binary, char *path);
bool			check_binary(char *binary, char *path, int *x);
bool			check_reg_file(mode_t st_mode);

//helpers
bool			get_close_chain(char *inst, int index);
bool			try_pwd(char *binary);
//char			*get_path(void);
int				ft_ischain(char *c);
int				ft_isquote(char c);
void			skip_quote(char *inst, int *x, char quote_type);
void			quote_prompt(char **instr, char *prompt);

#endif
