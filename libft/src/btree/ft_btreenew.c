/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 01:44:44 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:35:20 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"
#include <stddef.h>

t_btree	*ft_btreenew(void const *content, size_t content_size)
{
	t_btree *new;

	new = (t_btree *)ft_memalloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = ft_memalloc(content_size + 1);
		new->content_size = content_size;
		ft_memcpy(new->content, content, content_size);
	}
	return (new);
}
