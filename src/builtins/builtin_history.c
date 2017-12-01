/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:14:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 09:51:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "libft.h"

int builtin_history()
{
	t_shell *shell;
	t_cmds	*hist;
	int		x;

	x = 0;
	shell = sh_singleton();
	hist = shell->history;
	while (hist)
	{
		if (hist->cmd)
			ft_printf("%d  %s\n", ++x, hist->cmd);
		hist = hist->next;
	}
	return (0);
}
