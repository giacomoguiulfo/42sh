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

t_astree		*get_end(t_astree *node)
{
	while (node->right && node->right->type && node->right->type[0] == '|')
		node = node->right;
	node = node->right;
	return (node);
}

void			make_process(t_pipeline this, int out)
{
	this.this_path = build_bin_path(this.path, this.end->this->binary);
	setup_io(this.shell, this.end->this->redirs);
	if (this.this_path)
		this.end->ret = piped_fork(this, out);
}
