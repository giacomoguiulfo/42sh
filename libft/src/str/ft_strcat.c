/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:46:29 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 11:14:12 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's strcat() function, man strcat(3).
*/

char	*ft_strcat(char *s1, const char *s2)
{
	char *first;

	first = s1;
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (first);
}
