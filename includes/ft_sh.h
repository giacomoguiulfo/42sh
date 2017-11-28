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

typedef struct			s_terminal  // Added this entire struct
{
	t_darr				*newenvp;
	int					status;

	struct termios		term;
	char				*name;
	size_t				width;
	size_t				height;
	size_t				prompt_size;
}						t_terminal;

/*
** Main Functions
*/

int		msh_execute(char **args, t_darr *newenvp);
char	*readline(t_terminal *config);                 //Added

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

int		raw_terminal(t_terminal *config);          // Added

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
