/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:45:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:55:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <unistd.h>

void	ft_putstr(char const *s)
{
	if (s)
		write(STDOUT_FILENO, s, ft_strlen(s));
}
