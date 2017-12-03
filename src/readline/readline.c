/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 07:12:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_sh.h"
#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>

static void	input_constructor(t_input *data, t_cmds *history, char *prompt)
{
	data->prompt = prompt;
	data->prompt_size = ft_strlen(data->prompt);
	ft_bzero(data->char_buff, CHAR_BUFF_SIZE);
	ft_bzero(data->line_buff, LINE_BUFF_SIZE);
	data->line_size = 0;
	data->cursor_pos = 0;
	data->cursor_col = 0;
	data->cursor_row = 0;
	data->continue_loop = true;
	data->clipboard.copy_on = false;
	history->current = NULL;
	history->hit_end = false;
	if (history->init == false)
		history_constructor(history);
}

bool		exit_status(t_input *data, int ret)
{
	bool	quit;
	t_shell *shell;

	quit = false;
	if (data->char_buff[0] == 4)
	{
		quit = true;
		shell = sh_singleton();
		shell->quit = true;
		ft_putstr("\nFound EOF call\n");
	}
	else if (ret < 0)
	{
		quit = true;
		ft_putstr("\nRead error\n");
	}
	return (quit);
}

char		*readline(char *prompt)
{
	static t_cmds	history;
	t_input			data;
	t_keychain		key;
	int				ret;

	input_constructor(&data, &history, prompt);
	ft_putstr(prompt);
	while (data.continue_loop == true)
	{
		ret = read(0, &data.char_buff, 5);
		if (exit_status(&data, ret))
			exit(0);
		get_terminal_meta(&data);
		get_key(&data, &history, &key);
		if (key.found_key == true)
			key.this->action(&key);
		ft_bzero((void*)data.char_buff, CHAR_BUFF_SIZE);
	}
	ft_putchar('\n');
	if (ft_stris(data.line_buff, ft_isspace))
		return (NULL);
	history_add(&data, &history);
	return (ft_strdup(data.line_buff));
}
