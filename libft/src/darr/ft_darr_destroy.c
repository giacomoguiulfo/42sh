/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:01:05 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:01:18 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include <stdlib.h>

void		ft_darr_destroy(t_darr *array)
{
	if (array)
	{
		if (array->content)
			free(array->content);
		free(array);
	}
}
