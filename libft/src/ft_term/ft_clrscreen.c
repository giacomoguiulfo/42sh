/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clrscreen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:18:09 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/29 18:19:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_private.h"

void	ft_clrscreen(int rows)
{
	while (--rows >= 0)
	{
		ft_cursor_goto(0, rows);
		ft_termcmd("dl");
	}
}
