/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:23:16 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:37:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's isdigit() function, man isdigit(3).
*/

int		ft_isdigit(int c)
{
	return (((unsigned)c - 48) < 10u);
}
