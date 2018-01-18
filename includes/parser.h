/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/18 11:15:32 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_sh.h"
# include "libft.h"

typedef struct			s_asttoken
{
	char				*binary;
	char				**args;
	struct s_tokelist	**redirs;
	struct s_tokelist	*chain;
}						t_asttoken;

typedef struct			s_sub
{
	char				*start;
	char				*end;
	int					x;
}						t_sub;

t_asttoken				**synthesize_tokens(t_tokelist *tokens);
t_astree				*make_tree(t_asttoken **raw_materials);
void					substitution_requests(t_asttoken **pre_ast);
void					execute_ast_cmds(t_astree *head);
t_asttoken				**start_asttoken(void);
t_asttoken				**add_asttoken(t_asttoken **array);

void					add_astarg(t_asttoken *this, t_tokelist *tokens);
void					add_astredir(t_asttoken *this, t_tokelist *redir);
void					add_args(t_asttoken *build, t_tokelist *binary);
void					add_binary(t_asttoken *build, t_tokelist *binary);
void					add_chain(t_asttoken *build, t_tokelist *binary);
void					add_redir(t_asttoken *build, t_tokelist *binary);

bool					ft_issub(char c);

#endif
