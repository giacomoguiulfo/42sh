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

int builtin_cd();
int builtin_echo();
int builtin_env();
int builtin_exit();
int builtin_export();
int builtin_read();
int builtin_setenv();
int builtin_unset();
int builtin_unsetenv();
int builtin_history();

#endif
