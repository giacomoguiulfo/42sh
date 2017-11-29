/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

void	move_word(t_input *data, bool direction)
{
	data->width = data->width + 1 - 1;
	if (direction == true)
		ft_putstr("\nmoving right\n");
	else
		ft_putstr("\nmoving left\n");
}

void	move_row(t_input *data, bool direction)
{
	data->width = data->width + 1 - 1;
	if (direction == true)
		ft_putstr("\nmoving down\n");
	else
		ft_putstr("\nmoving up\n");
}