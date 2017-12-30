/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:05:47 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:06:02 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"

void		ft_darr_set(t_darr *array, int i, void *el)
{
	if (!(i < array->size))
		return ;
	if (i > array->len)
		array->len = i;
	array->content[i] = el;
}
