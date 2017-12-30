/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_underline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:44:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:02:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_private.h"
#include <stdbool.h>

void	ft_underline(bool set)
{
	if (set == true)
		ft_termcmd("us");
	else if (set == false)
		ft_termcmd("ue");
}
