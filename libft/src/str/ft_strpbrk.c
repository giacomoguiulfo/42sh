/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:48:25 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/16 12:05:07 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strpbrk(const char *s, const char *charset)
{
	char	*c;

	while (*s)
	{
		c = (char *)charset;
		while (*c)
		{
			if (*c == *s)
				return ((char *)s);
			c++;
		}
		s++;
	}
	return (NULL);
}
