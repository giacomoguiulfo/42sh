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

static void	input_constructor(t_input *data, char *prompt)
{
	t_shell	*shell;

	shell = sh_singleton();
	shell->prompt = prompt;
	shell->continue_loop = true;
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
}

bool		exit_status(t_input *data, int ret)
{
	if (data->char_buff[0] == 4)
	{
		ft_putstr("\nTrash: Found EOF call\n");
		sh_singleton()->continue_loop = false;
		sh_singleton()->quit = true;
		return (true);
	}
	else if (sh_singleton()->continue_loop == false)
	{
		return (true);
	}
	else if (ret < 0)
	{
		ft_printf("return is %d\n", ret);
		ft_putstr("\nTrash: Read error\n");
		return ((sh_singleton()->quit = true));
	}
	return (false);
}

char		*readline(char *prompt)
{
	t_input			data;
	t_keychain		key;

	input_constructor(&data, prompt);
	ft_putstr(prompt);
	while (sh_singleton()->continue_loop == true)
	{
		data.ret = read(0, &data.char_buff, 5);
		if (exit_status(&data, data.ret))
			return (NULL);
		get_terminal_meta(&data);
		get_key(&data, &key);
		if (key.found_key == true)
			key.this->action(&key);
		ft_bzero((void*)data.char_buff, data.ret);
	}
	ft_putchar('\n');
	if (ft_stris(data.line_buff, ft_isspace))
		return (NULL);
	return (ft_strdup(data.line_buff));
}
