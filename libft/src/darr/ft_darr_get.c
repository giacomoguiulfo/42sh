/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:54:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:02:23 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include <stddef.h>

void		*ft_darr_get(t_darr *array, int i)
{
	if (!(i < array->size))
		return (NULL);
	return (array->content[i]);
}
