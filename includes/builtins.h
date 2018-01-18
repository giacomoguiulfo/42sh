/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:55:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/17 17:29:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "libft.h"

# define READ_OPT_LR (1 << 0)
# define READ_OPT_LU (1 << 0)
# define READ_HAS_OPT_LR(a) (a & READ_OPT_LR)
# define READ_HAS_OPT_LU(a) (a & READ_OPT_LU)

typedef int		(t_builtin)(const char *av[]);

typedef struct	s_read
{
	t_optparser optparser;
	t_dstr		input;
	int			fd;
	char		delim;
}				t_read;

int				builtin_cd(char *av[]);
int				builtin_echo(char *av[]);
int				builtin_env(char *av[]);
int				builtin_exit(void);
int				builtin_export(char *av[]);
int				builtin_read(char *av[]);
int				builtin_setenv(char *av[]);
int				builtin_unset(char *av[]);
int				builtin_unsetenv(char *av[]);
int				builtin_history();

#endif
