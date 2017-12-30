/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:17:21 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/29 13:14:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"
#include "libft.h"
#include <stddef.h>

void	ft_dstr_append(t_dstr *dstr, char *newdata)
{
	size_t nd_len;

	if (!newdata || !newdata[0])
		return ;
	nd_len = ft_strlen(newdata);
	if (dstr->cap < dstr->len + nd_len)
		ft_dstr_resize(dstr, dstr->len + nd_len);
	ft_memcpy(dstr->data + dstr->len, newdata, nd_len);
	dstr->len += nd_len;
}
