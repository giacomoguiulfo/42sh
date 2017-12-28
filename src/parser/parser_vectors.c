/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/13 16:31:52 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"

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
		this->args = (char**)ft_hmalloc(sizeof(char*) * (2 + 1));
		this->args[0] = this->binary;
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
		new[x] = this->args[x];
	new[x] = ft_hstrndup(tmp->content, tmp->len);
	this->args = new;
}
