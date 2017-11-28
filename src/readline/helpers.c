/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 07:11:57 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <unistd.h>
#include <term.h>

void	clear_line(t_input *data)
{
	move_home(data);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	data->cursor_pos = 0;
	data->line_size = 0;
}
