/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:16:03 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/25 18:09:26 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int builtin_echo(char *const av[])
{
	av++;
	while (*av)
	{
		ft_putstr(*av);
		(av + 1) ? ft_putchar(' ') : 0;
		av++;
	}
	ft_putchar('\n');
	return (0);
}
