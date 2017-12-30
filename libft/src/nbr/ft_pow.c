/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 17:41:42 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:46:55 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Simplier version of libm's pow() function, man pow(3).
*/

double	ft_pow(double x, int y)
{
	double temp;

	if (y == 0)
		return (1);
	temp = ft_pow(x, y / 2);
	if (y % 2 == 0)
		return (temp * temp);
	else
	{
		if (y > 0)
			return (x * temp * temp);
		else
			return ((temp * temp) / x);
	}
}
