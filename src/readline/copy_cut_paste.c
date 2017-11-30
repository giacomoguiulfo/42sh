/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termios.h>

void	copy_cut_paste(t_input *data, t_text *clipboard, int mode)
{
	if (mode == 0)
		ft_putstr("\nPressed pg up: copy\n");
	else if (mode == 1)
		ft_putstr("\nPressed pg dn: cut\n");
	else if (mode == 2)
		ft_putstr("\nPressed del: start copy\n");
	data->width = data->width + 1 - 1;
	clipboard->copy_on = true;
	clipboard->copy_on = false;
}