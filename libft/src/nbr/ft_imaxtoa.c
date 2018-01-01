/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:34:09 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:34:38 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

char	*ft_imaxtoa(intmax_t value)
{
	uintmax_t	i;
	intmax_t	size;
	char		*ret;

	i = (value < 0) ? -value : value;
	size = 1 + (value < 0);
	while ((i /= 10))
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = (value < 0) ? -value : value;
	ret[--size] = "0123456789"[i % 10];
	while ((i /= 10))
		ret[--size] = "0123456789"[i % 10];
	if (value < 0)
		ret[--size] = '-';
	return (ret);
}
