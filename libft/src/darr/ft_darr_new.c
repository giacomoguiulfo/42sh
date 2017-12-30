/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:03:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:03:37 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darr.h"
#include "libft.h"
#include <stddef.h>

void		*ft_darr_new(t_darr *array)
{
	if (!(array->content_size > 0))
		return (NULL);
	return (ft_memalloc(array->content_size));
}
