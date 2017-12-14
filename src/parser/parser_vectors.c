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

	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) * (1 + 1));
	new[1] = 0;
	new[0] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[0]->binary = NULL;
	new[0]->args = NULL;
	new[0]->redirs = NULL;
	new[0]->chain = NULL;
	return (new);
}

t_asttoken	**add_asttoken(t_asttoken **array)
{
	int			size;
	int			x;
	t_asttoken	**new;

	size = -1;
	while (array[++size])
		;
	new = (t_asttoken**)ft_hmalloc(sizeof(t_asttoken*) * (size + 1 + 1));
	new[size + 1] = 0;
	new[size] = (t_asttoken*)ft_hmalloc(sizeof(t_asttoken));
	new[size]->binary = NULL;
	new[size]->args = NULL;
	new[size]->redirs = NULL;
	new[size]->chain = NULL;
	x = -1;
	while (++x < size)
		new[x] = array[x];
	array = new;
	return (new);
}

void	add_astredir(t_asttoken *this, t_tokelist *redir)
{
	t_tokelist	**new;
	int			size;
	int			x;

	if (!this->redirs)
	{
		this->redirs = (t_tokelist**)ft_hmalloc(sizeof(t_tokelist*) * (1 + 1));
		this->redirs[1] = 0;
		this->redirs[0] = redir;
		return ;
	}
	size = -1;
	while (this->redirs[++size])
		;
	new = (t_tokelist**)ft_hmalloc(sizeof(t_tokelist*) * (size + 1 + 1));
	new[size + 1] = 0;
	new[size] = redir;
	x = -1;
	while (++x < size)
		new[x] = this->redirs[x];
	this->redirs = new;
}

void	add_astarg(t_asttoken *this, t_tokelist *tmp)
{
	char	**new;
	int		size;
	int		x;

	if (!this->args)
	{
		this->args = (char**)ft_hmalloc(sizeof(char*) + 1 + 1);
		this->args[0] = this->binary;
		this->args[1] = 0;
		return ;
	}
	size = -1;
	while (this->args[++size])
		;
	ft_printf("size is %d\n", size);
	new = (char**)ft_hmalloc(sizeof(char*) * (size + 1 + 1));
	new[size + 1] = 0;
	x = -1;
	while (++x < size)
		new[x] = this->args[x];
	ft_printf("size: %d, x: %d\n", size, x);
	new[x] = ft_hstrndup(tmp->content, tmp->len);
	new[x + 1] = 0;
	this->args = new;
	x = -1;
	while (this->args[++x])
		ft_printf("args: %s\n", this->args[x]);
}
