/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:57:30 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:19:45 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		len;
	char	*ret;

	if (!format || !*format)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(&ret, format, ap);
	if (write(1, ret, len) < 0)
		return (-1);
	free(ret);
	va_end(ap);
	return (len);
}

int		ft_vasprintf(char **ret, const char *format, va_list ap)
{
	if (*format == '\0')
		*ret = ft_strnew(0);
	if (!ret || !format || !*format)
		return (0);
	if (ft_strchr(format, '%') == NULL)
	{
		if ((*ret = ft_strdup(format)) == NULL)
			return (-1);
		return (ft_strlen(*ret));
	}
	return (ft_strprintf(ret, format, ap));
}

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list ap;
	int		len;
	char	*ret;

	if (!str || !format)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(&ret, format, ap);
	ft_strcpy(str, ret);
	free(ret);
	va_end(ap);
	return (len);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	int		len;
	char	*ret;

	if (!str || !format)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(&ret, format, ap);
	if (size == 0)
		return (len);
	else if (size - 1 == 0)
		str[0] = '\0';
	ft_strncpy(str, ret, size - 1);
	free(ret);
	va_end(ap);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list ap;
	int		len;
	char	*ret;

	if (!format || !*format || fd < 0)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(&ret, format, ap);
	if (write(fd, ret, len) < 0)
		return (-1);
	free(ret);
	va_end(ap);
	return (len);
}
