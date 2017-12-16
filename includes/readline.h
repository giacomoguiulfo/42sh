/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 07:10:10 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "ft_sh.h"
# include <unistd.h>
# include <stdbool.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdlib.h>

# define LINE_BUFF_SIZE 4096
# define CHAR_BUFF_SIZE 5

# define KEY_DELETE		127
# define KEY_DOWN		66
# define KEY_END		70
# define KEY_ENTER		10
# define KEY_HOME		72
# define KEY_LEFT		68
# define KEY_RIGHT		67
# define KEY_UP			65
# define KEY_CTRL_C		3

typedef struct			s_text
{
	bool				copy_on;
	bool				copied;
	char				temp_buff[LINE_BUFF_SIZE];
	size_t				start;
	size_t				end;	
}						t_text;

typedef struct			s_input
{
	bool				continue_loop;
	char				char_buff[CHAR_BUFF_SIZE];
	char				line_buff[LINE_BUFF_SIZE];
	char				*prompt;
	size_t				cursor_col;
	size_t				cursor_pos;
	size_t				cursor_row;
	size_t				end_col;
	size_t				end_row;
	size_t				height;
	size_t				line_size;
	size_t				prompt_size;
	size_t				ret;
	size_t				width;
	struct winsize		window_size;
	struct s_text		clipboard;
}						t_input;

typedef struct			s_keychain
{
	struct s_key		**list;
	struct s_key		*this;
	t_input				*data;
	t_cmds				*history;
	bool				found_key;
}						t_keychain;

typedef struct			s_key
{
	char				name[10];
	char				id;
	void				(*action)(t_keychain *);
}						t_key;

char	*readline(char *prompt);
void	copy_cut_paste(t_input *data, t_text *clipboard, int mode);
void	get_key(t_input *data, t_cmds *history, t_keychain *find);
void	insert(t_input *data);
void	trim(t_input *data);

void	history_add(t_input *data, t_cmds *head);
void	history_change(t_input *data, t_cmds *history, bool direction);
void	history_cleanup(t_cmds *history);
void	history_constructor(t_cmds *history);

void	move_end(t_input *data);
void	move_home(t_input *data);
void	move_left(t_input *data);
void	move_right(t_input *data);
void	move_row(t_input *data, bool direction);
void	move_word(t_input *data, bool direction);

bool	str_protection(t_input *data, size_t first, size_t second);
void	clear_insert(t_input *data);
void	gather_position_data(t_input *data);
void	get_terminal_meta(t_input *data);
void	print_end_col_pad(size_t cursor_col);
void 	start_stop_highlight(t_input *data, t_text *clipboard);

void	enter_key(struct s_keychain *master);
void	print_key(struct s_keychain *master);
void	opt_move_key(struct s_keychain *master);
void	move_key(struct s_keychain *master);

#endif
