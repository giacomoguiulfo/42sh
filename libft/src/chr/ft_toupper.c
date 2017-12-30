/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:47:16 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:41:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's toupper() function, man toupper(3).
*/

int		ft_toupper(int c)
{
	return (((unsigned)c - 97) < 26u ? c - 32 : c);
}
