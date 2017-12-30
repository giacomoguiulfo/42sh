/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_goto.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:29:05 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:02:50 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <term.h>
#include <stddef.h>
#include <unistd.h>

void	ft_cursor_goto(int x, int y)
{
	char *str1;
	char *str2;

	if ((str1 = tgetstr("cm", NULL)) != NULL)
	{
		if ((str2 = tgoto(str1, x, y)) != NULL)
			ft_putstr_fd(str2, STDERR_FILENO);
	}
}
