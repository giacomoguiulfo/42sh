/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 11:50:08 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:32:20 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_base(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)));
}

int			ft_atoi_base(char *str, int base)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	result = 0;
	if (base <= 1 || base > 36)
		return (0);
	while (ISSPACE(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (ft_is_in_base(str[i], base))
	{
		if (str[i] - 'A' >= 0)
			result = result * base + (str[i++] - 'A' + 10);
		else
			result = result * base + (str[i++] - '0');
	}
	if (i > 19)
		return ((sign == 1) ? -1 : 0);
	return ((int)result * sign);
}
