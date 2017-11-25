/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:51:59 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:37:55 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Description:
** Equivalent of libm's sqrtf() function, man sqrtf(3).
*/

float ft_sqrtf(float x)
{
	float ret;

	ret = 1.0f;
	while (ABS((ret * ret) / x - 1.0f) >= 0.0000001f)
		ret -= (ret * ret - x) / (2 * ret);
	return (ret);
}
