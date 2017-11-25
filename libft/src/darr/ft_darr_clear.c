/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:00:21 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:00:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include <stdlib.h>

void		ft_darr_clear(t_darr *array)
{
	int i;

	i = 0;
	if (array->content_size > 0)
	{
		while (i < array->len)
		{
			if (array->content[i] != NULL)
				free(array->content[i]);
			++i;
		}
	}
}
