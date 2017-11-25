/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:22:57 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 13:55:21 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"
#include <stdlib.h>

void	ft_dstr_free(t_dstr *dstr)
{
	if (dstr->data && dstr->cap > 0)
	{
		free(dstr->data);
		dstr->data = NULL;
	}
}
