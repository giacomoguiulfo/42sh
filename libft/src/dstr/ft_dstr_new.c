/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:21:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:13:30 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"
#include "libft.h"
#include <stddef.h>

int		ft_dstr_new(t_dstr *dstr, size_t init_cap)
{
	if (!dstr || !init_cap)
		return (-1);
	dstr->len = 0;
	dstr->cap = init_cap;
	if ((dstr->data = ft_memalloc(sizeof(char) * dstr->cap)) == NULL)
		return (-1);
	return (0);
}
