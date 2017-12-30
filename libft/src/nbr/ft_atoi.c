/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:06:41 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:32:40 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Description:
** Equivalent to libc's atoi() function, man atoi(3).
*/

int		ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	result = 0;
	while (ISSPACE(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (ISDIGIT(str[i]))
		result = result * 10 + str[i++] - '0';
	if (i > 19 || result > 9223372036854775807)
		return ((sign == 1) ? -1 : 0);
	return ((int)result * sign);
}
