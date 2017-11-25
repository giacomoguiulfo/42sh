/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:17:24 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:58:49 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stddef.h>

/*
** Description:
** Equivalent to libc's strndup() function, man strndup(3).
*/

char	*ft_strndup(const char *src, size_t len)
{
	char	*dst;
	char	*cdst;

	if (!(dst = ft_strnew(len + 1)))
		return (0);
	cdst = dst;
	len++;
	while (--len > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (cdst);
}
