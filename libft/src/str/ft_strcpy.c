/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:08:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/20 11:15:54 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
** Equivalent to libc's strcpy() function, man strcpy(3).
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
