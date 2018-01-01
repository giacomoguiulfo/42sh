/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:56:47 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/23 11:05:07 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_basename(const char *path)
{
	char *basename;

	basename = ft_strrchr(path, '/');
	return ((basename) ? basename + 1 : (char *)path);
}
