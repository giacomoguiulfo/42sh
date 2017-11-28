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

#include "../../includes/readline.h"
#include "../../includes/ft_sh.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

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
	tputs(tgetstr("le", NULL), 1, ft_intputchar);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	tputs(tgetstr("im", NULL), 1, ft_intputchar);
	ft_fputstr(buff);
	tputs(tgetstr("ei", NULL), 1, ft_intputchar);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	data->cursor_pos--;
	data->line_size--;
}
