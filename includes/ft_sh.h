/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 19:28:33 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include <unistd.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdlib.h>

# define MSH_RL_SIZ 1024

# define LINE_BUFF_SIZE 4096
# define CHAR_BUFF_SIZE 5

# define ENTER 10
# define DELETE 127
# define UP 65
# define DOWN 66
# define LEFT 68
# define RIGHT 67
# define HOME 72
# define END 70

# define SAVEPOS "sc"
# define MOVERIGHT "nd"
# define MOVELEFT "le"
# define MOVEUP "up"
# define MOVEDN "do"
# define LINESTART "cr"

typedef struct			s_cmds
{
	struct s_cmds		*next;
	struct s_cmds		*prev;
	struct s_cmds		*end;
	struct s_cmds		*current;
	char				*cmd;
}						t_cmds;

typedef struct			s_input
{
	char				char_buff[CHAR_BUFF_SIZE];
	char				line_buff[LINE_BUFF_SIZE];
	size_t				line_size;
	size_t				cursor_pos;
	size_t				cursor_col;
	size_t				cursor_row;
	size_t				end_col;
	size_t				end_row;
	bool				continue_loop;

	struct s_cmds		history;
}						t_input;

typedef struct			s_terminal
{
	t_darr				*newenvp;
	int					status;

	struct termios		term;
	struct winsize		window_size;
	char				*name;
	size_t				width;
	size_t				height;

	size_t				prompt_size;
}						t_terminal;


/*
** Main Functions
*/

int		msh_execute(char **args, t_darr *newenvp);

/*
** Need to be organized
*/

char	*readline(t_terminal *config);
int		raw_terminal(t_terminal *config);
void	get_window_size(t_terminal *config);
int		ft_intputchar(int c);

void	history_add(t_cmds *head, char *cmd);
t_cmds	*history_constructor(void);
void	history_up(t_terminal *config, t_input *data, t_cmds *history);
void	history_dn(t_terminal *config, t_input *data, t_cmds *history);

void	move_home(t_terminal *config, t_input *data);
void	move_end(t_input *data);

/*
** Builtins
*/

int		msh_exit(char **args);
int		msh_cd(char **args, t_darr *newenvp);
int		msh_echo(char **args, t_darr *newenvp);
int		msh_displ_env(t_darr *newenvp);
int		msh_setenv(char **args, t_darr *newenvp);
int		msh_unsetenv(char **args, t_darr *newenvp);

/*
** Utils
*/

size_t	msh_put_arrow(void);
char	**msh_strsplit(char *line);
char	*msh_check_bin(char *executable, char *path);
char	*msh_get_env(t_darr *newenvp, char *look);
int		msh_envcmp(char *env, char *lookup);
char	**msh_cp_env(t_darr *newenvp);
int		msh_env_idx(t_darr *newenvp, char *var);
int		msh_env_inval(char *str);
int		msh_senv_helper(char *str, t_darr *newenvp, char *tmp);

/*
** Extras
*/

int		msh_help(char **args);
void	echo_esc_chr(char esc);

#endif
