/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:43:39 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:02:15 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_private.h"
#include <stdbool.h>

void	ft_highlight(bool set)
{
	if (set == true)
		ft_termcmd("so");
	else if (set == false)
		ft_termcmd("se");
}
