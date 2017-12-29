/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:04:59 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/13 12:17:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ft_sh.h"
# include "lexer.h"

void	check_pipes(t_astree *node);
void	execute_ast_cmds(t_astree *head);
void	setup_io(t_shell *shell, t_tokelist **redirs);

char	*build_bin_path(char *path, char *binary);

bool	check_access(char *binary, char *path);
bool	check_builtin(char *binary);
bool	check_reg_file(mode_t st_mode);

#endif
