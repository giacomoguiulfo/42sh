/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 19:14:58 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:39:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's isspace() function, man isspace(3).
*/

int		ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}
