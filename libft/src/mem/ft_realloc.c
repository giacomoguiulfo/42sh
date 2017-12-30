/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:38:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/30 08:15:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdlib.h>

/*
** Description:
** The ft_realloc function is similar to realloc(3), but it always allocates
** new space instead of reallocating even if there is more continous space
** of memory available.
**
** Parameters:
** (1) Pointer to allocated memory (2) Size of the allocated memory
** (3) Number of bytes for the new allocation
**
** Return values:
** The ft_realloc() function returns a pointer to the new allocated memory.
** If the 'new_size' parameter had the value of zero, it will only free
** the memory previously allocated. If the 'ptr' parameter is NULL, the
** function will return a pointer to a new allocation of memory. If the 'new
** size' parameter is smaller or equal to 'src_size', the function returns
** the same pointer that it received as first argument.
**
** If an error occurs, ft_realloc() returns NULL.
*/

void	*ft_realloc(void *ptr, size_t src_size, size_t new_size)
{
	void *new_ptr;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (ptr);
	}
	if (!ptr)
		return (malloc(new_size));
	if (new_size <= src_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, src_size);
		free(ptr);
	}
	return (new_ptr);
}
