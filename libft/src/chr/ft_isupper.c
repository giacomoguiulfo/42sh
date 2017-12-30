/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 23:57:27 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:39:42 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's isupper() function, man isupper(3).
*/

int		ft_isupper(int c)
{
	return ((c >= 'A' && c <= 'Z'));
}
