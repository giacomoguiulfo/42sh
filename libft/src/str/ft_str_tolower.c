/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:37:46 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/22 14:55:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft.h"
#include <stddef.h>

char	*ft_str_tolower(char *str)
{
	int		len;
	int		i;
	char	*ret;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	i = -1;
	while (++i < len)
		ret[i] = TOLOWER(str[i]);
	ret[len] = '\0';
	return (ret);
}
