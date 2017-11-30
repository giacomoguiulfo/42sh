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

// KEYS:
// opt-page_up = paste
// page_up     = copy
// page_dn     = cut
// delete      = start highlight

static void	clear_highlights(t_input *data)
{
	size_t row;
	size_t col;

	row = data->cursor_row;
	col = data->prompt_size % data->width;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_putstr(data->line_buff);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

static void start_stop_highlight(t_input *data, t_text *clipboard)
{
	if (clipboard->copy_on == false)
	{
		clipboard->copy_on = true;
		clipboard->start = data->cursor_pos;
		clipboard->end = data->cursor_pos;
		tputs(tgetstr("so", NULL), 1, ft_putchar);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgetstr("ic", NULL), 1, ft_putchar);
		ft_putchar(data->line_buff[data->cursor_pos]);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
	}
	else
	{
		clipboard->copy_on = false;
		tputs(tgetstr("se", NULL), 1, ft_putchar);
		clear_highlights(data);
		data->clipboard.start = 0;
		data->clipboard.end = 0;
	}
}

static void	copy(t_input *data, t_text *clipboard)
{
	ft_bzero(clipboard->temp_buff, LINE_BUFF_SIZE);
	ft_strncpy(clipboard->temp_buff, data->line_buff + clipboard->start, clipboard->end - clipboard->start);
	start_stop_highlight(data, clipboard);
	clipboard->copy_on = false;
	clipboard->copied = true;
}

static void paste(t_input *data, t_text *clipboard)
{
	data->width = data->width - 1 + 1;
	ft_putstr(clipboard->temp_buff);
}

void	copy_cut_paste(t_input *data, t_text *clipboard, int mode)
{
	if (mode == 0 && clipboard->copy_on == true)
		copy(data, clipboard);
	else if (mode == 1 && clipboard->copy_on == true)
		ft_putstr("cut this shit, yo\n");
	else if (mode == 2)
		start_stop_highlight(data, clipboard);
	else if (mode == 3 && clipboard->copied == true)
		paste(data, clipboard);
}
