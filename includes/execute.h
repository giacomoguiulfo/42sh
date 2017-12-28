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

void	execute_ast_cmds(t_astree *head);

bool	check_reg_file(mode_t st_mode);
bool	check_access(char *binary, char *path);

#endif
