/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:21:37 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/13 12:26:09 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include <stddef.h>

char		*ft_hstrndup(char *hstr, size_t size)
{
	char	*ret;
	size_t	i;

	if (!hstr)
		return (NULL);
	ret = (char*)ft_hmalloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = -1;
	while (++i < size)
		ret[i] = hstr[i];
	return (ret);
}
