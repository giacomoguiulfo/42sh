/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by gguiulfo         ###   ########.fr       */
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

typedef struct			s_astree
{
	char				*type;
	int					ret;
	int					pipe_fd[2];
	struct s_asttoken	*this;
	struct s_astree		*left;
	struct s_astree		*right;	
}						t_astree;

t_asttoken	**synthesize_tokens(t_tokelist *tokens);
t_astree	*make_tree(t_asttoken **raw_materials);
void		execute_ast_cmds(t_astree *head);

t_asttoken	**start_asttoken(void);
t_asttoken	**add_asttoken(t_asttoken **array);
void		add_astarg(t_asttoken *this, t_tokelist *tokens);
void		add_astredir(t_asttoken *this, t_tokelist *redir);

#endif
