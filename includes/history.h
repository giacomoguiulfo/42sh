/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

#include "ft_sh.h"
#include "readline.h"
#include <stdbool.h>

struct s_input;
struct s_cmds;

void	history_add(char *cmd);
void	history_change(t_input *data, t_cmds *history, bool direction);
void	history_cleanup(t_cmds *history);
void	history_constructor(t_cmds *history);

#endif
