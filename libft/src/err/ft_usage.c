/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:19:08 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 11:17:51 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_usage(char const *name, char const *str)
{
	ft_dprintf(STDERR_FILENO, "%{bred}usage: %s%s%{eoc}\n", name, str);
	exit(EXIT_FAILURE);
}
