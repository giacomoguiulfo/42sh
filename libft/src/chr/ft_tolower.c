/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:52:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:41:08 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's tolower() function, man tolower(3).
*/

int		ft_tolower(int c)
{
	return (((unsigned)c - 65) < 26u ? c + 32 : c);
}
