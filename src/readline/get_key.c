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

void	history_change(t_input *data, t_cmds *history, bool opt);

void	opt_move_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	if (master->data->char_buff[3] == 'D') //left
		move_word(master->data, false);
	else if (master->data->char_buff[3] == 'C') //right
		move_word(master->data, true);
	else if (master->data->char_buff[3] == 'B') //down
		move_row(master->data, false);
	else if (master->data->char_buff[3] == 'A') //up
		move_row(master->data, true);
}

void	move_key(struct s_keychain *master)
{
	if (master->data->char_buff[2] == KEY_LEFT)
		move_left(master->data);
	else if (master->data->char_buff[2] == KEY_RIGHT)
		move_right(master->data);
	if (master->data->clipboard.copy_on == false)
	{
		if (master->data->char_buff[2] == KEY_UP)
			history_change(master->data, master->history, true);
		else if (master->data->char_buff[2] == KEY_DOWN)
			history_change(master->data, master->history, false);
	}
}

void	new_quote_prompt(t_keychain *master, char *instr, char *prompt)
{
	char	*new_instr;
	char	*tmp;
	char	buff[4096];

	new_instr = readline(prompt);
	if (!new_instr)
		return ;
	ft_bzero((void*)buff, 4096);
	ft_strcpy(buff, master->data->line_buff);
	ft_strcat(buff, new_instr);
	ft_strcpy(master->data->line_buff, buff);
	master->data->line_size += ft_strlen(new_instr);
	ft_asprintf(&tmp, "%s%s", instr, new_instr);
	free(new_instr);
	instr = ft_strdup(tmp);
	free(tmp);
}

void	enter_key(struct s_keychain *master)
{
	char *ptr;

	if (master->data->line_buff[master->data->line_size - 1] == '\\')
	{
		while (master->data->line_buff[master->data->line_size - 1] == '\\')
		{
			master->data->line_buff[master->data->line_size - 1] = '\n';
			ptr = master->data->line_buff;
			ft_putchar('\n');
			new_quote_prompt(master, ptr, "> ");
		}
	}
	master->data->continue_loop = false;
	return ;
}

void	print_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	insert(master->data);
	return ;
}

void	home_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_home(master->data);
}

void	end_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	move_end(master->data);
}

void	delete_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		return ;
	else if (master->data->cursor_pos == 0)
		return ;
	trim(master->data);
}

void	edit_key(struct s_keychain *master)
{
	if (master->data->char_buff[0] == -30 && master->data->char_buff[1] == -119) //x
		copy_cut_paste(master->data, &master->data->clipboard, 1);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -102) //v
		copy_cut_paste(master->data, &master->data->clipboard, 3);
	else if (master->data->char_buff[0] == -61 && master->data->char_buff[1] == -89) //c
		copy_cut_paste(master->data, &master->data->clipboard, 0);
	else if (master->data->char_buff[0] == -30 && master->data->char_buff[2] == -85) //b
		copy_cut_paste(master->data, &master->data->clipboard, 2);
}

void	ctrl_c_key(struct s_keychain *master)
{
	if (master->data->clipboard.copy_on == true)
		start_stop_highlight(master->data, &master->data->clipboard);
	ft_bzero((void*)master->data->line_buff, LINE_BUFF_SIZE);
	ft_putchar('\n');
	ft_putstr(master->data->prompt);
	master->data->cursor_pos = 0;
	master->data->line_size = 0;
	master->data->clipboard.copy_on = false;
}

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

void	get_key(t_input *data, t_keychain *find)
{
	find->data = data;
	find->history = (sh_singleton())->history;
	find->found_key = true;
	if (ft_isprint(data->char_buff[0])) // regular chars
		find->this = &g_key[0];
	else if (data->char_buff[0] == KEY_DELETE) // delete
		find->this = &g_key[9];
	else if (data->char_buff[2] == g_key[3].id) //move left
		find->this = &g_key[3];
	else if (data->char_buff[2] == g_key[4].id) //move right
		find->this = &g_key[4];
	else if (data->char_buff[2] == g_key[2].id) //opt-move
		find->this = &g_key[2];
	else if (data->char_buff[2] == g_key[5].id) //move up
		find->this = &g_key[5];
	else if (data->char_buff[2] == g_key[6].id) //move down
		find->this = &g_key[6];
	else if (data->char_buff[0] == g_key[1].id) //enter key
		find->this = &g_key[1];
	else if (data->char_buff[2] == g_key[7].id) //home key
		find->this = &g_key[7];
	else if (data->char_buff[2] == g_key[8].id) //end key
		find->this = &g_key[8];
	else if (data->char_buff[0] < 0) //edit keys
		find->this = &g_key[10];
	else if (data->char_buff[0] == g_key[11].id) //ctrl-c key
		find->this = &g_key[11];
	else
	{
		find->found_key = false;
		ft_putstr("\nKash: Unknown key\n");
	}
}
