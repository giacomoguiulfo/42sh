/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:33:26 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:25:52 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Description:
** Equivalent to libc's bzero() function, man bzero(3).
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = 0;
}
