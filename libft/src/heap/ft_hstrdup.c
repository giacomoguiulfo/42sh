/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:19:48 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/13 12:25:51 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_hstrdup(char *hstr)
{
	char	*ret;
	size_t	size;
	size_t	i;

	if (!hstr)
		return (NULL);
	size = -1;
	while (hstr[++size])
		;
	ret = (char*)ft_hmalloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = -1;
	while (++i < size)
		ret[i] = hstr[i];
	return (ret);
}
