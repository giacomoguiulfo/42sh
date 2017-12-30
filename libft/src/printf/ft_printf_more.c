/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:56:39 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:20:29 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list ap;
	int		len;

	if (!format || !*format)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(ret, format, ap);
	if (len < 0)
		return (-1);
	va_end(ap);
	return (len);
}

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	int		len;
	char	*ret;

	if (!format || !*format || fd < 0)
		return (0);
	len = ft_vasprintf(&ret, format, ap);
	if (write(fd, ret, len) < 0)
		return (-1);
	free(ret);
	return (len);
}
