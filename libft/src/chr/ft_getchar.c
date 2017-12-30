/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:21:10 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 10:42:09 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/*
** Description:
** This function is equivalent to libc's getchar() function, man getchar(3).
*/

int		ft_getchar(void)
{
	static char	buf[BUFSIZ];
	static char	*bufp = buf;
	static int	n = 0;

	if (n == 0)
	{
		n = read(STDIN_FILENO, buf, sizeof(buf));
		bufp = buf;
	}
	return ((--n >= 0) ? (unsigned char)*bufp++ : EOF);
}
