/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:35:21 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/07 13:42:41 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

void	ft_sstrdel(char ***sstr)
{
	size_t i;

	if (!sstr)
		return ;
	i = 0;
	while ((*sstr)[i])
	{
		ft_strdel((*sstr) + i);
		i++;
	}
	ft_strdel((*sstr) + i);
	free(*sstr);
	*sstr = NULL;
}
