/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 08:21:08 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:15:18 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "libft.h"
#include <stddef.h>

void	*ft_hmemalloc(size_t size)
{
	void	*ptr;

	ptr = ft_hmalloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}
