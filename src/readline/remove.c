/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_sh.h"
#include <term.h>

void	remove(t_input *data)
{
	char	buff[LINE_BUFF_SIZE];
	char	*tmp;

	if (data->cursor_pos == 0)
		return ;
	ft_bzero((void*)buff, ft_strlen(data->line_buff + 1));
	tmp = &data->line_buff[data->cursor_pos - 1];
	*tmp = '\0';
	ft_strcpy(buff, tmp + 1);
	ft_strcpy(data->line_buff + data->cursor_pos - 1, buff);
	if (data->cursor_col == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, data->width), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	ft_putstr(buff);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	data->cursor_pos--;
	data->line_size--;
}
