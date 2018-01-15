/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

void	manage_pipes(t_astree *node)
{
	if (node->this->chain && node->this->chain->type[0] == '|')
	{
		pipe(node->right->pipe_fd);
		dup2(node->right->pipe_fd[0], 0);
		close(node->right->pipe_fd[0]);
	}
	if (node->pipe_fd[0] > -1)
	{
		dup2(node->pipe_fd[1], 0);
		close(node->pipe_fd[0]);
		close(node->pipe_fd[1]);
	}
}

void	check_pipes(t_astree *node)
{
	char	*chain;

	chain = node->this->chain->type;
	if (chain && chain[0] == '|' && chain[1] != '|')
		manage_pipes(node);
	else if (node->pipe_fd[0] > -1)
		manage_pipes(node);
}
