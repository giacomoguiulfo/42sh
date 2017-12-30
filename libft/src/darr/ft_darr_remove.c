/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:04:27 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:04:40 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include <stddef.h>

void		*ft_darr_remove(t_darr *array, int i)
{
	void *el;

	el = array->content[i];
	array->content[i] = NULL;
	return (el);
}
