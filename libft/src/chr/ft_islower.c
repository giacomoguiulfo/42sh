/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 00:02:50 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:38:25 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's islower() function, man islower(3).
*/

int		ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}
