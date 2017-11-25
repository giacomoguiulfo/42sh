/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:26:13 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 11:06:43 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** Description:
** The ft_putnchar_fd() function replicates the behaviour of ft_putchar_fd()
** the number of times specified in the parameter 'n'.
**
** Parameters:
** (1) The character to write (2) The number of times to write the specified
** character (3) The file descriptor where the characters will be written.
**
** Return Values:
** If successful, the ft_putnchar_fd() function returns the number of bytes
** written. If an error occurs, the funtion returns -1.
*/

int	ft_putnchar_fd(int c, int n, int fd)
{
	int	ret;
	int total;

	total = n;
	while (n-- > 0)
	{
		ret = write(fd, &c, 1);
		if (ret == -1)
			return (-1);
	}
	return (total);
}
