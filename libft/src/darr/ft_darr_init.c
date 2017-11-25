/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:02:30 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:02:49 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include "libft.h"
#include <stdlib.h>

t_darr *ft_darr_init(size_t content_size, size_t initial_size)
{
	t_darr *array;

	if ((array = (t_darr *)malloc(sizeof(t_darr))) == NULL)
		return (NULL);
	if ((array->size = initial_size) == 0)
		return (NULL);
	array->content = (void **)ft_memalloc(sizeof(void *) * initial_size);
	if (array->content == NULL)
		return (NULL);
	array->len = 0;
	array->content_size = content_size;
	array->expand_rate = DARR_EXPAND_RATE;
	return (array);
}
