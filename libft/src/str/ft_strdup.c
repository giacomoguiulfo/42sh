/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:11:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 06:46:27 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Description:
** Equivalent to libc's strdup() function, man strdup(3).
*/

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	dup = (char*)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
