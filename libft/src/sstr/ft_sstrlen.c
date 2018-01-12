/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:33:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:33:15 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_sstrlen(char *const sstr[])
{
	size_t i;

	i = 0;
	while (sstr[i])
		i++;
	return (i);
}