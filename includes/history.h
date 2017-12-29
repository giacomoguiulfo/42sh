/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/16 20:22:50 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "ft_sh.h"
# include "readline.h"
# include <stdbool.h>

void	history_add(char *cmd);
void	history_change(t_input *data, t_cmds *history, bool direction);
void	history_cleanup(t_cmds *history);
void	history_constructor(t_shell *shell, t_cmds *history);

#endif
