/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:03:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:13:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stdlib.h>

void		*ft_hmalloc(size_t size)
{
	t_heap_man	*heap_man;
	t_memnode	*new;
	void		*ptr;

	if ((new = malloc(size + sizeof(t_memnode))) == NULL)
		return (NULL);
	ptr = (char *)new + sizeof(t_memnode);
	new->ptr = ptr;
	new->next = NULL;
	heap_man = ft_heap_singleton();
	if (heap_man->first == NULL)
	{
		heap_man->first = new;
		heap_man->last = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->prev = heap_man->last;
		heap_man->last->next = new;
		heap_man->last = new;
	}
	return (ptr);
}
