/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_contract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:00:38 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:00:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include <stddef.h>

int					ft_darr_contract(t_darr *array)
{
	size_t new_size;

	if (array->len < (int)array->expand_rate)
		new_size = array->expand_rate;
	else
		new_size = array->len;
	return (ft_darr_resize(array, new_size + 1));
}
