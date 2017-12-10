/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asttoken_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "ft_sh.h"

t_asttoken	**start_asttoken(void)
{
	t_asttoken **new;

	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) + 1 + 1);
	new[1] = 0;
	new[0] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[0]->binary = NULL;
	new[0]->args = NULL;
	new[0]->redirs = NULL;
	new[0]->chain = NULL;
	return (new);
}

t_asttoken	*add_asttoken(t_asttoken **array)
{
	int			size;
	int			x;
	t_asttoken	**new;

	size = -1;
	while (array[++size])
		;
	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) + size + 1 + 1);
	new[size + 1] = 0;
	new[size] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[size]->binary = NULL;
	new[size]->args = NULL;
	new[size]->redirs = NULL;
	new[size]->chain = NULL;
	x = -1;
	while (x < size)
		new[x] = array[x];
	array = new;
	return (new[size]);
}

void	add_astarg(t_asttoken *this, char **arg_array, char *arg)
{
	char	**new;
	int		size;
	int		x;

	if (!arg_array)
	{
		arg_array = (char**)ft_hmalloc(sizeof(char*) + 2 + 1);
		arg_array[0] = this->binary;
		arg_array[1] = ft_hstrdup(arg);
		arg_array[2] = 0;
		this->args = arg_array;
		return ;
	}
	size = -1;
	while (arg_array[++size])
		;
	new = (char**)ft_hmalloc(sizeof(char*) * (size + 1 + 1));
	new[size + 1] = 0;
	x = -1;
	while (++x < size)
		new[x] = arg_array[x];
	new[x] = ft_hstrdup(arg);
	this->args = new;
}

/*
typedef struct			s_asttoken
{
	char				*binary;
	char				**args;
	struct s_tokelist	*redirs;
	struct s_tokelist	*chain;
}						t_asttoken;*/