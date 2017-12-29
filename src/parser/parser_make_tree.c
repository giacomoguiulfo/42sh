/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"

t_astree	*make_tree_node(void)
{
	t_astree	*new;

	new = (t_astree*)ft_hmalloc(sizeof(t_astree));
	new->left = NULL;
	new->right = NULL;
	new->this = NULL;
	new->type = NULL;
	new->pipe_fd[0] = -2;
	new->pipe_fd[1] = -2;
	return (new);
}

t_astree	*make_left_branch(t_astree *current, t_asttoken *toke)
{
	current->left = make_tree_node();
	current->left->type = toke->chain->type;
	current = current->left;
	return (current);
}

t_astree	*make_right_branch_pipe(t_astree *current, t_asttoken *toke)
{
	current->right = make_tree_node();
	current->right->type = toke->chain->type;
	current = current->right;
	return (current);
}

t_astree	*make_right_branch_semi_colon(t_astree *head, t_asttoken *toke)
{
	t_astree *tmp;

	tmp = head;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = make_tree_node();
	tmp->right->type = toke->chain->type;
	return (tmp->right);
}

t_astree	*make_tree(t_asttoken **raw)
{
	int			x;
	t_astree	*head;
	t_astree	*tmp;

	x = -1;
	head = make_tree_node();
	tmp = head;
	while (raw[++x])
	{
		tmp->this = raw[x];
		tmp->type = raw[x]->chain->type;
		if (raw[x]->chain && raw[x]->chain->type[0] == '&' &&
			raw[x]->chain->type[1] == '&')
			tmp = make_left_branch(tmp, raw[x]);
		else if (raw[x]->chain && raw[x]->chain->type[0] == '|' &&
			raw[x]->chain->type[1] == '|')
			tmp = make_left_branch(tmp, raw[x]);
		else if (raw[x]->chain && raw[x]->chain->type[0] == '|')
			tmp = make_right_branch_pipe(tmp, raw[x]);
		else if (raw[x]->chain && raw[x]->chain->type[0] == ';')
			tmp = make_right_branch_semi_colon(head, raw[x]);
	}
	return (head);
}
