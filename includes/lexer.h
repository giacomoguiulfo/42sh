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
	int					ret;
	int					state;
	int					size;
	int					x;
}						t_toke;

//tokenize
t_tokelist		*tokenize(char	*instructions);

void			tokenize_chain(char *instr, t_toke *help, t_tokelist *head);
void			tokenize_redirections(char *instr, t_toke *help, t_tokelist *head);
void			tokenize_words(char *instr, t_toke *help, t_tokelist *head);
void			tokenize_quotes(char *instr, t_toke *help, t_tokelist *head);

//helpers
bool			ft_isredirection(char c);
int				ft_iscompletechain(char *str);
int				ft_isdepchain(char *c);
int				ft_isfilename(char c);

//utils
t_tokelist 		*add_toke(t_tokelist *head);
t_tokelist 		*start_toking(void);

//validate
bool			validate_quotes(char *inst);
int				validate_chains(char *inst);

//helpers
bool			get_close_chain(char *inst, int index);
bool			try_pwd(char *binary);
int				ft_ischain(char *c);
int				ft_isquote(char c);
void			skip_quote(char *inst, int *x, char quote_type);
void			quote_prompt(char **instr, char *prompt);

#endif
