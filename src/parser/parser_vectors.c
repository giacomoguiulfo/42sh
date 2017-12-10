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
	ft_putstr("Before ASTTOKEN\n");
	while (array[++size])
		;
	ft_putstr("After first while loop ASTTOKEN\n");
	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) + size + 1 + 1);
	new[size + 1] = 0;
	new[size] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[size]->binary = NULL;
	new[size]->args = NULL;
	new[size]->redirs = NULL;
	new[size]->chain = NULL;
	x = -1;
	ft_putstr("Before SECOND ASTTOKEN\n");
	while (++x < size)
		new[x] = array[x];
	ft_putstr("AFTER SECOND ASTTOKEN\n");
	array = new;
	return (new[size]);
}

void	add_astarg(t_asttoken *this, t_tokelist *tmp)
{
	char	**new;
	int		size;
	int		x;

	if (!this->args)
	{
		this->args = (char**)ft_hmalloc(sizeof(char*) + 2 + 1);
		this->args[0] = this->binary;
		ft_printf("arg value: %s, len value: %d\n", tmp->content, tmp->len);
		this->args[1] = ft_hstrndup(tmp->content, tmp->len);
		this->args[2] = 0;
		return ;
	}
	size = -1;
	while (this->args[++size])
		;
	new = (char**)ft_hmalloc(sizeof(char*) * (size + 1 + 1));
	new[size + 1] = 0;
	x = -1;
	while (++x < size)
	{
		new[x] = this->args[x];
		ft_printf("new array: %s\n", new[x]);
	}
	new[x] = ft_hstrndup(tmp->content, tmp->len);
	ft_printf("New string: %s\n", new[x]);
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