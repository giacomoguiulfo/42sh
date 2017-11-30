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
	data->width = data->width + 1 - 1;
	if (clipboard->copy_on == false && (mode == 0 || mode == 1 || mode == 2))
	{
		clipboard->copy_on = true;
		tputs(tgoto(tgetstr("so", NULL), 0, data->width - 1), 1, ft_putchar);
	}
	else if (clipboard->copy_on == true)
	{
		clipboard->copy_on = false;
		tputs(tgoto(tgetstr("se", NULL), 0, data->width - 1), 1, ft_putchar);
	}

}