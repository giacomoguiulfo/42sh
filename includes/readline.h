/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 19:28:33 by gguiulfo         ###   ########.fr       */
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

typedef struct			s_cmds
{
	bool				init;
	char				*cmd;
	struct s_cmds		*current;
	struct s_cmds		*end;
	struct s_cmds		*next;
	struct s_cmds		*prev;
}						t_cmds;

typedef struct			s_input
{
	bool				continue_loop;
	char				char_buff[CHAR_BUFF_SIZE];
	char				line_buff[LINE_BUFF_SIZE];
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

char	*readline(size_t prompt);
void	insert(t_input *data);
void	remove(t_input *data);

void	history_constructor(t_cmds *history);
void	history_add(t_cmds *head, char *cmd);
void	history_dn(t_input *data, t_cmds *history);
void	history_up(t_input *data, t_cmds *history);

void	move_cursor(t_input *data, t_cmds *history);
void	move_end(t_input *data);
void	move_home(t_input *data);
void	move_left(t_input *data);
void	move_right(t_input *data);

void	clear_line(t_input *data);
int		ft_isblank(int c);
int		ft_intputchar(int c);
int		valid_string(char *str);

#endif
