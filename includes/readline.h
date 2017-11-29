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

# define CTRLUP			21
# define CTRLDN			4
# define CTRLEF			"[5"
# define CTRLRI			18

# define DELETE			127
# define DOWN			66
# define END			70
# define ENTER			10
# define HOME			72
# define LEFT			68
# define RIGHT			67
# define UP				65

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
}						t_input;

char	*readline(char *prompt);
void	insert(t_input *data);
void	remove(t_input *data);

void	history_add(t_cmds *head, char *cmd);
void	history_change(t_input *data, t_cmds *history, bool direction);
void	history_cleanup(t_cmds *history);
void	history_constructor(t_cmds *history);

void	move_cursor(t_input *data, t_cmds *history);
void	move_end(t_input *data);
void	move_home(t_input *data);
void	move_left(t_input *data);
void	move_right(t_input *data);

void	gather_position_data(t_input *data);
void	print_end_col_pad(size_t cursor_col);

#endif
