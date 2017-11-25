/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:04:59 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:13:10 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stdlib.h>

int		ft_heap_clear(void)
{
	t_heap_man	*heap_man;
	t_memnode	*memnode;
	t_memnode	*next;

	heap_man = ft_heap_singleton();
	if (heap_man == NULL)
		return (1);
	memnode = heap_man->first;
	while (memnode != NULL)
	{
		next = memnode->next;
		free(memnode);
		memnode = next;
	}
	free(heap_man);
	return (0);
}
