/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_remove_nth.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:52:50 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 13:59:47 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*
** Description:
** Removes the nth element of an array of any type.
**
** Parameters:
** (1) Index of item to remove (2) Pointer to the start of the array
** (3) Size of each element (4) Number of elements in the array
*/

void	ft_arr_remove_nth(int nth, void *array, size_t size, int len)
{
	unsigned char	*elem;

	if (!array || !size || !len)
		return ;
	elem = (((unsigned char *)array) + (nth * size));
	ft_memmove((void *)elem, (void *)(elem + size), (len - nth - 1) * size);
}
