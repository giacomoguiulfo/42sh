/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_singleton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 03:14:21 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/28 04:36:14 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"
#include <stddef.h>

t_shell *sh_singleton(void)
{
	static t_shell *shell = NULL;

	if (shell == NULL)
		shell = ft_memalloc(sizeof(t_shell));
	return (shell);
}
