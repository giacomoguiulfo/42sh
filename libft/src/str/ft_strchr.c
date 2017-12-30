/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:26:37 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:56:45 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Description:
** Equivalent to libc's strchr() function, man strchr(3).
*/

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	a;

	a = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == a)
		return ((char *)(s + i));
	return (NULL);
}
