/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/20 09:12:47 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_sh.h"
#include <stdbool.h>

static void	clear_line(t_input *data)
{
	int row;

	row = data->cursor_row;
	while (row-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}
/*
void		gather_this_data(t_input *data)
{
	data->end_col = (data->prompt_size + data->line_size) % data->width;
	data->end_row = (data->prompt_size + data->line_size) / data->width;
	data->cursor_row = (data->prompt_size + data->cursor_pos) / data->width;
	data->cursor_col = (data->prompt_size + data->cursor_pos) % data->width;
}
*/
//fix this from messing up multiple line edits

static int	ft_special_len(char *str, int width, int prompt_len)
{
	int x;
	int special;
	//int holderrow;
	int holdercol;

	x = -1;
	special = 0;
	while (str[++x])
	{
		if (str[x] == '\n')
		{
			holdercol = (x + prompt_len) % width;
			//holderrow = (x + prompt_len) / width;
			//ft_printf("row: %d, col: %d\n\n", holderrow, holdercol);
			special += holdercol;
			//special += (holderrow * width);
		}
		else
			special++;
	}
	return (special);
}

static void	print(t_input *data, t_cmds *history)
{
	int x;
	int special;

	ft_putstr(history->current->cmd);
	ft_strcpy(data->line_buff, history->current->cmd);
	special = ft_special_len(history->current->cmd, data->prompt_size, data->width);
	//ft_printf("special len: %d\n", special);
	data->cursor_pos = ft_strlen(history->current->cmd);
	data->line_size = data->cursor_pos;
	data->end_col = (special) % data->width;
	data->end_row = (special) / data->width;
	data->cursor_col = (data->prompt_size + special) % data->width;
	//data->cursor_row = (data->prompt_size + special) / data->width;
	if (data->end_col == 0)
		print_end_col_pad(data->cursor_col);
	tputs(tgoto(tgetstr("ch", NULL), 0, data->cursor_col), 1, ft_putchar);
	x = data->end_row - data->cursor_row;
	//ft_printf("x up: %d\n", x);
	while (--x > 0)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
}

static bool	get_history(t_cmds *history, bool direction)
{
	if (direction == true && history->hit_end == false)
	{
		history->current = history->end;
	}
	else if (direction == false && history->hit_end == true)
	{
		history->current = history;
		history->hit_end = false;
	}
	else
		return (0);
	return (1);
}

static void	iterate(t_cmds *history, bool direction)
{
	if (direction == true)
	{
		history->current = history->current->prev;
		if (!history->current)
			history->hit_end = true;
	}
	else
		history->current = history->current->next;
}

void		history_change(t_input *data, t_cmds *history, bool direction)
{
	clear_line(data);
	ft_putstr(data->prompt);
	data->cursor_pos = 0;
	if (!history->current || !history->current->cmd)
	{
		if (!get_history(history, direction))
			return ;
	}
	else if (history->current->cmd)
	{
		iterate(history, direction);
	}
	if (history->current && history->current->cmd)
		print(data, history);
	else
	{
		ft_bzero(data->line_buff, data->line_size);
		data->line_size = 0;
		data->cursor_pos = 0;
	}
}
