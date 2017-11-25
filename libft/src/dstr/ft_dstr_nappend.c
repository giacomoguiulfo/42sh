/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_nappend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:22:26 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 13:56:15 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"
#include "libft.h"
#include <stddef.h>

void	ft_dstr_nappend(t_dstr *dstr, char *newdata, size_t n)
{
	size_t nd_len;

	nd_len = n;
	if (dstr->cap < dstr->len + nd_len)
		ft_dstr_resize(dstr, dstr->len + nd_len);
	ft_memcpy(dstr->data + dstr->len, newdata, nd_len);
	dstr->len += nd_len;
}
