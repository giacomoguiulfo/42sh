/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unixcase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:33:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/12 14:26:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chr.h"
#include <stddef.h>

int	ft_unixcase(const char *str)
{
	size_t i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_' &&
																str[0] != '/'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}
