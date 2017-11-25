/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/25 01:17:26 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "builtins.h"

# include "libft.h"

# define MSH_RL_SIZ 1024

typedef struct  s_shell
{
  char          **env;
}               t_shell;

t_shell  *shell_singleton(void);

/*
** Main Functions
*/

int		msh_execute(char **args);

/*
** Builtins
*/

// int		msh_exit(char **args);
// int		msh_cd(char **args);
// int		msh_echo(char **args);
// int		msh_setenv(char **args);
// int		msh_unsetenv(char **args);

/*
** Utils
*/

void	msh_put_arrow(void);
char	**msh_strsplit(char *line);
// char	*msh_check_bin(char *executable, char *path);
// int		msh_envcmp(char *env, char *lookup);
// char	**msh_cp_env(t_darr *newenvp);
// int		msh_env_idx(t_darr *newenvp, char *var);
// int		msh_env_inval(char *str);
// int		msh_senv_helper(char *str, char *tmp);

/*
** Extras
*/

// int		msh_help(char **args);
// void	echo_esc_chr(char esc);

#endif
