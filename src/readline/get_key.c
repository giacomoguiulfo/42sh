/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 07:12:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "history.h"

t_key		g_key[] = {
	{"print", 0, &print_key},
	{"enter", KEY_ENTER, &enter_key},
	{"opt-move", '[', &opt_move_key},
	{"move left", KEY_LEFT, &move_key},
	{"move right", KEY_RIGHT, &move_key},
	{"move up", KEY_UP, &move_key},
	{"move down", KEY_DOWN, &move_key},
	{"move home", KEY_HOME, &home_key},
	{"move end", KEY_END, &end_key},
	{"delete", KEY_DELETE, &delete_key},
	{"edit text", 0, &edit_key},
	{"ctrl-c", KEY_CTRL_C, &ctrl_c_key}
};

void	new_quote_prompt(t_keychain *master, char *prompt)
{
	char	*new_instr;
	char	buff[4096];

	ft_putchar('\n');
	new_instr = readline(prompt);
	if (!new_instr)
		return ;
	ft_bzero((void*)buff, 4096);
	ft_strcpy(buff, master->data->line_buff);
	ft_strcat(buff, new_instr);
	ft_strcpy(master->data->line_buff, buff);
	master->data->line_size += ft_strlen(new_instr);
	free(new_instr);
}

void	enter_key(struct s_keychain *master)
{
	if (master->data->line_buff[master->data->line_size - 1] == '\\')
	{
		while (master->data->line_buff[master->data->line_size - 1] == '\\')
		{
			master->data->line_buff[master->data->line_size - 1] = '\n';
			new_quote_prompt(master, "> ");
		}
	}
	master->data->continue_loop = false;
	return ;
}

bool	additional_keys(t_input *data, t_keychain *find)
{
	bool	test;

	test = false;
	if (data->char_buff[2] == g_key[3].id && (test = true))
		find->this = &g_key[3];
	else if (data->char_buff[2] == g_key[4].id && (test = true))
		find->this = &g_key[4];
	else if (data->char_buff[2] == g_key[2].id && (test = true))
		find->this = &g_key[2];
	else if (data->char_buff[2] == g_key[5].id && (test = true))
		find->this = &g_key[5];
	else if (data->char_buff[2] == g_key[6].id && (test = true))
		find->this = &g_key[6];
	else if (data->char_buff[0] == g_key[1].id && (test = true))
		find->this = &g_key[1];
	else if (data->char_buff[2] == g_key[7].id && (test = true))
		find->this = &g_key[7];
	else if (data->char_buff[2] == g_key[8].id && (test = true))
		find->this = &g_key[8];
	else if (data->char_buff[0] < 0 && (test = true))
		find->this = &g_key[10];
	else if (data->char_buff[0] == g_key[11].id && (test = true))
		find->this = &g_key[11];
	return (test);
}

void	get_key(t_input *data, t_keychain *find)
{
	find->data = data;
	find->history = (sh_singleton())->history;
	find->found_key = true;
	if (ft_isprint(data->char_buff[0]))
		find->this = &g_key[0];
	else if (data->char_buff[0] == KEY_DELETE)
		find->this = &g_key[9];
	else if (additional_keys(data, find))
		return ;
	else
	{
		find->found_key = false;
		ft_putstr("\nTrash: Unknown key\n");
	}
}
