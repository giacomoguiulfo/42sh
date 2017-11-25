/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 06:01:09 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:23:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include <stddef.h>

t_list			*ft_lstfind(t_list *begin_list, void *data, int (*cmp)())
{
	t_list *node;

	node = begin_list;
	while (node)
	{
		if ((cmp)(node->content, data) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
