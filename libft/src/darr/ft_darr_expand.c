/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:01:32 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:01:52 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include "libft.h"
#include <stddef.h>

int					ft_darr_expand(t_darr *array)
{
	size_t old_size;

	old_size = array->size;
	if (ft_darr_resize(array, array->size + array->expand_rate) != 0)
		return (-1);
	ft_memset(array->content + old_size, 0, array->expand_rate + 1);
	return (0);
}
