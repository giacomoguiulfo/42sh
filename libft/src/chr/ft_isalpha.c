/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:50 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:36:13 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's isalpha() function, man isalpha(3).
*/

int		ft_isalpha(int c)
{
	return (((unsigned)c | 32) - 97 < 26u);
}
