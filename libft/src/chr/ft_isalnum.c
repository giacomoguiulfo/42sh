/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:09:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:36:20 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's isalnum() function, man isalnum(3).
*/

int		ft_isalnum(int c)
{
	return ((((unsigned)c | 32) - 97 < 26u) || ((unsigned)c - 48) < 10u);
}
