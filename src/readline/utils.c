/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <stdbool.h>

bool	str_protection(size_t first, size_t second)
{
	size_t overflow;

	overflow = first + second;
	if (overflow > LINE_BUFF_SIZE - 1)
	{
		ft_printf("Error: buffer length %zu exceeded", LINE_BUFF_SIZE);
		ft_printf(" by %zu characters\n", overflow - LINE_BUFF_SIZE);
		return (false);
	}
	return (true);
}
