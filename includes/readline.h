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

# define DELETE			127
# define DOWN			66
# define END			70
# define ENTER			10
# define HOME			72
# define LEFT			68
# define RIGHT			67
# define UP				65

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
	size_t				width;
	struct winsize		window_size;
	struct s_text		clipboard;
}						t_input;

struct t_key;

typedef struct		s_klist
{
	struct s_key	**list;
	t_input			*data;
	t_cmds			*history;
	struct s_key	*this;
}					t_klist;

typedef struct	s_key
{
	char		name[10];
	char		id;
	void		(*handle)(t_klist *);
}				t_key;

char	*readline(char *prompt);
void	copy_cut_paste(t_input *data, t_text *clipboard, int mode);
void	get_key(t_input *data, t_cmds *history, t_klist *find);
void	insert(t_input *data);
void	trim(t_input *data);

void	history_add(t_input *data, t_cmds *head);
void	history_change(t_input *data, t_cmds *history, bool direction);
void	history_cleanup(t_cmds *history);
void	history_constructor(t_cmds *history);

void	move_cursor(t_input *data, t_cmds *history);
void	move_end(t_input *data);
void	move_home(t_input *data);
void	move_left(t_input *data);
void	move_right(t_input *data);
void	move_row(t_input *data, bool direction);
void	move_word(t_input *data, bool direction);

bool	str_protection(t_input *data, size_t first, size_t second);
void	gather_position_data(t_input *data);
void	get_terminal_meta(t_input *data);
void	print_end_col_pad(size_t cursor_col);

void	enter_key(struct s_klist *master);
void	print_key(struct s_klist *master);

#endif
