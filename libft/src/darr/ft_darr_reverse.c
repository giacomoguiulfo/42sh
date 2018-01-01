/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:05:14 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:05:38 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include "libft.h"
#include <stddef.h>

void		ft_darr_reverse(t_darr *array)
{
	int len;
	int i;

	if (array == NULL || array->len == 0)
		return ;
	i = 0;
	len = FT_DARR_COUNT(array) - 1;
	while (i < len)
	{
		ft_swap(array->content[i], array->content[len], array->content_size);
		++i;
		--len;
	}
}
