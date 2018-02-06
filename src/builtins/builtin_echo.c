/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:16:03 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/08 11:54:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The echo utility writes its arguments to standard output, followed by
** a <newline>.  If there are no arguments, only the <newline> is written.
**
** @param av - arguments
** @return
*/

int	builtin_echo(char **av)
{
	av++;
	while (*av)
	{
		ft_putstr(*av);
		*(av + 1) ? ft_putchar(' ') : 0;
		av++;
	}
	ft_putchar('\n');
	return (0);
}
