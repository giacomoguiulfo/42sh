/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 05:43:38 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/28 05:44:40 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>

int	ft_isdir(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb))
		return (0);
	return (S_ISDIR(sb.st_mode));
}
