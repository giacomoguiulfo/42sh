/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:55:15 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/24 17:02:03 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef int	(t_builtin)(const char *av[]);

int builtin_cd(char *argv[]);
int builtin_echo(char *argv[]);
int builtin_env(char *argv[]);
int builtin_exit(void);
int builtin_export(char *argv[]);
int builtin_setenv(char *argv[]);
int builtin_unset(char *argv[]);
int builtin_unsetenv(char *argv[]);
int builtin_history();

#endif
