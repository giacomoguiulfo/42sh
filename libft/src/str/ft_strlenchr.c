/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:44:45 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 21:48:08 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t ft_strlenchr(char *str, char c)
{
	size_t i;

	i = 0;
	while (*str && *(str++) != c)
		i++;
	return (i);
}
