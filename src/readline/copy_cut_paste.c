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

void		start_stop_highlight(t_input *data, t_text *clipboard)
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
		clear_highlights(data, true);
	}
}

static void	copy(t_input *data, t_text *clip)
{
	if (!str_protection(data, data->line_size, clip->end - clip->start))
		return ;
	ft_bzero(clip->temp_buff, LINE_BUFF_SIZE);
	ft_strncpy(clip->temp_buff, data->line_buff + clip->start,
		clip->end - clip->start + 1);
	start_stop_highlight(data, clip);
	clip->copy_on = false;
	clip->copied = true;
}

static void	cut(t_input *data, t_text *clip)
{
	char	buff[LINE_BUFF_SIZE];

	if (!str_protection(data, data->line_size, clip->end - clip->start))
		return ;
	ft_bzero(buff, LINE_BUFF_SIZE);
	copy(data, clip);
	ft_strncpy(buff, data->line_buff, clip->start);
	ft_strcpy(buff + clip->start, data->line_buff + clip->end + 1);
	ft_strcpy(data->line_buff, buff);
	clear_highlights(data, false);
	data->line_size = ft_strlen(data->line_buff);
	data->cursor_pos = data->line_size;
}

static void	paste(t_input *data, t_text *clip)
{
	char	buff[LINE_BUFF_SIZE];
	int		x;

	if (!str_protection(data, data->line_size, clip->end - clip->start))
		return ;
	ft_bzero(buff, LINE_BUFF_SIZE);
	ft_strncpy(buff, data->line_buff, data->cursor_pos);
	ft_strcpy(buff + data->cursor_pos, clip->temp_buff);
	ft_strcpy(buff + data->cursor_pos + ft_strlen(clip->temp_buff),
		data->line_buff + data->cursor_pos);
	ft_strcpy(data->line_buff, buff);
	clear_highlights(data, false);
	data->line_size = ft_strlen(data->line_buff);
	data->cursor_pos = data->line_size;
	gather_position_data(data);
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
	tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col), 1, ft_putchar);
	x = data->end_row - data->cursor_row;
	while (x-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
}

void		copy_cut_paste(t_input *data, t_text *clipboard, int mode)
{
	if (mode == 0 && clipboard->copy_on == true)
		copy(data, clipboard);
	else if (mode == 1 && clipboard->copy_on == true)
		cut(data, clipboard);
	else if (mode == 2)
		start_stop_highlight(data, clipboard);
	else if (mode == 3 && clipboard->copied == true)
		paste(data, clipboard);
}
