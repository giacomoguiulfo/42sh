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
	struct s_tokelist	*redirs;
	struct s_tokelist	*chain;
}						t_asttoken;

t_asttoken	**start_asttoken(void);
t_asttoken	*add_asttoken(t_asttoken **array);
void		add_astarg(t_asttoken *this, char **arg_array, char *arg);

#endif
