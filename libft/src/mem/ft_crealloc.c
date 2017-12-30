/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:17:05 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/30 08:19:04 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "libft.h"

void	*ft_crealloc(void *ptr, int size)
{
	void	*new;

	new = ft_memalloc(size);
	ft_memcpy(new, ptr, ft_strlen(ptr));
	ft_memdel(&ptr);
	return (new);
}
