/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 23:04:55 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:35:03 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	unsigned int	i;
	int				size;
	char			*ret;

	value = (base != 10 && value < 0) ? -value : value;
	i = (base == 10 && value < 0) ? -value : value;
	size = 1 + (base == 10 && value < 0);
	while ((i /= base))
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = (base == 10 && value < 0) ? -value : value;
	ret[--size] = "0123456789ABCDEF"[i % base];
	while ((i /= base))
		ret[--size] = "0123456789ABCDEF"[i % base];
	if ((base == 10) && value < 0)
		ret[--size] = '-';
	return (ret);
}
