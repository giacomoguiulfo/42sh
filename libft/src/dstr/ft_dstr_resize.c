/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:21:44 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:18:40 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"
#include "libft.h"
#include <stddef.h>

void	ft_dstr_resize(t_dstr *dstr, size_t min)
{
	size_t	mllc_size;

	if (!(dstr->data))
		ft_dstr_new(dstr, min);
	mllc_size = dstr->cap;
	while (mllc_size < min)
		mllc_size *= 2;
	dstr->data = (char *)ft_memrealloc(dstr->data, dstr->len, mllc_size);
	dstr->cap = mllc_size;
}
