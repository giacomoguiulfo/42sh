/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:44:32 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:29:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Description:
** Equivalent to libc's memccpy() function, man memccpy(3).
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned const char	*s_str;
	unsigned char		*d_str;
	unsigned char		chr;

	d_str = (unsigned char *)dst;
	s_str = (unsigned const char *)src;
	chr = (unsigned char)c;
	while (n--)
		if ((*d_str++ = *s_str++) == chr)
			return ((void *)d_str);
	return (NULL);
}
