/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:31:19 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 05:55:18 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

int	builtin_env(void)
{
	ft_sstrputs(sh_singleton()->env);
	// TODO: Run a program in a modified environment
	return (0);
}
