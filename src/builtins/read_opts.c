/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:55:46 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/11 11:46:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_sh.h"
#include "libft.h"

int			read_get_fd(char *def, char *fd, t_read *data)
{
	(void)def;
	if (!data)
		return (1);
	data->fd = ft_atoi(fd);
	return (0);
}
