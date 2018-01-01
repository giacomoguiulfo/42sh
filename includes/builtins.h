/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:55:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/25 20:20:00 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef int	(t_builtin)(const char *av[]);

int builtin_cd(char *av[]);
int builtin_echo(char *av[]);
int builtin_env(char *av[]);
int builtin_exit(void);
int builtin_export(char *av[]);
int builtin_read(char *av[]);
int builtin_setenv(char *av[]);
int builtin_unset(char *av[]);
int builtin_unsetenv(char *av[]);
int builtin_history();

#endif
