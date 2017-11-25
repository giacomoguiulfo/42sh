/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:58:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:01:29 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s || (str = (char *)malloc(sizeof(char))) == 0)
		return (0);
	if (*s == '\0' || !s)
		return (str);
	while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	while (s[i])
		i++;
	while ((s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n') && i)
		i--;
	if ((str = ft_strnew(i)) == 0)
		return (0);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	return (str);
}
