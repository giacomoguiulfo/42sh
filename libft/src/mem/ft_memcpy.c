/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:45:40 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:30:18 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Description:
** Equivalent to libc's memcpy() function, man memcpy(3).
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d_str;
	const unsigned char	*s_str;

	d_str = (unsigned char *)dst;
	s_str = (const unsigned char *)src;
	while (n--)
		*d_str++ = *s_str++;
	return (dst);
}
