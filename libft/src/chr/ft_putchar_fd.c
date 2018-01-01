/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:51:00 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 11:16:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** Description:
** Writes the character c to the file descriptor fd.
**
** Parameters:
** (1) The character to write (2) The file descriptor
**
** Return Value:
** This function returns 1 when successful or -1 if an error occurs.
*/

int	ft_putchar_fd(int c, int fd)
{
	return ((int)write(fd, &c, 1));
}
