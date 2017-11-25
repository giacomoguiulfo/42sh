/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:38:33 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:16:50 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "libft.h"
#include <stdlib.h>

static void	*srealloc_node(t_memnode *start, size_t src_size, size_t new_size)
{
	t_heap_man	*heap_man;
	t_memnode	*new_node;

	if ((new_node = malloc(new_size + sizeof(t_memnode))) == NULL)
		return (NULL);
	ft_memcpy(new_node, start, src_size + sizeof(t_memnode));
	free(start);
	heap_man = ft_heap_singleton();
	if (new_node->prev == NULL)
		heap_man->first = new_node;
	else
		new_node->prev->next = new_node;
	if (new_node->next == NULL)
		heap_man->last = new_node;
	else
		new_node->next->prev = new_node;
	new_node->ptr = (char *)new_node + sizeof(t_memnode);
	return (new_node->ptr);
}

void		*ft_hrealloc(void *ptr, size_t src_size, size_t new_size)
{
	t_memnode	*start;

	if (!new_size)
	{
		if (ptr)
			ft_hfree(ptr);
		return (ptr);
	}
	if (ptr == NULL)
		return (ft_hmalloc(sizeof(new_size)));
	if (new_size <= src_size)
		return (ptr);
	start = (t_memnode *)((char *)ptr - sizeof(t_memnode));
	ptr = srealloc_node(start, src_size, new_size);
	return (ptr);
}
