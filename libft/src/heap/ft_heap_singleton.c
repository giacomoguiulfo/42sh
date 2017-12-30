/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_singleton.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "libft.h"
#include <stddef.h>

t_heap_man	*ft_heap_singleton(void)
{
	static t_heap_man	*heap_man;

	if (heap_man == NULL)
		heap_man = ft_memalloc(sizeof(t_heap_man));
	return (heap_man);
}
