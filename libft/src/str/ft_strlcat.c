/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:29:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:58:00 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stddef.h>

/*
** Description:
** Equivalent to libc's strlcat() function, man strlcat(3).
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t returnval;

	if (size + ft_strlen(src) > ft_strlen(src) + ft_strlen(dst))
		returnval = ft_strlen(src) + ft_strlen(dst);
	else
		returnval = ft_strlen(src) + size;
	while (*dst && size > 0)
	{
		dst++;
		size--;
	}
	if (size < 1)
		return (returnval);
	size--;
	while (*src && size > 0)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (returnval);
}
