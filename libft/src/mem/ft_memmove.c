/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:35:43 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:30:32 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Description:
** Equivalent to libc's memmove() function, man memmove(3).
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d_str;
	unsigned char	*s_str;
	int				size;

	size = (int)len;
	d_str = (unsigned char *)dst;
	s_str = (unsigned char *)src;
	if (s_str < d_str)
	{
		while (--size > -1)
			d_str[size] = s_str[size];
	}
	else
	{
		while (size--)
			*d_str++ = *s_str++;
	}
	return (dst);
}
