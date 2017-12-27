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

t_astree	*make_left_branch(t_astree *current/*, int opt*/)
{
	ft_printf("Make left branch\n");
	current->left = make_tree_node();
	current = current->left;
	/*if (opt == 1)
		ft_putstr("you just made a left branching &&\n");
	else if (opt == 2)
		ft_putstr("you just made a left branching ||\n");*/
	return (current);
}

t_astree	*make_right_branch_pipe(t_astree *current)
{
	ft_printf("Make right branch pipe\n");
	current->right = make_tree_node();
	current = current->right;
	//ft_putstr("You just made aright branching pipe\n");
	return (current);
}

t_astree	*make_right_branch_semi_colon(t_astree *head)
{
	t_astree *tmp;

	ft_printf("Make right branch semi-colon\n");
	tmp = head;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = make_tree_node();
	tmp = tmp->right;
	//ft_printf("You just made a new right branching ; that re-started off the head node\n");
	return (tmp);
}

void		print_tree(t_astree *head, int *node_count)
{
	t_astree *tmp;

	tmp = head;
	/*if (head->this->binary)
		ft_printf("Binary for %d is %s\n", *node_count, head->this->binary);
	else
		ft_printf("No binary found for node %d\n", *node_count);*/
	*node_count = *node_count + 1;
	if (tmp->left)
	{
		//ft_printf("Dependent branches fond on the left--checking these first\n");
		print_tree(tmp->left, node_count);
	}
	if (tmp->right)
	{
		//ft_printf("Checking out a right side branch\n");
		print_tree(tmp->right, node_count);
	}
}

t_astree	*make_tree(t_asttoken **raw_materials)
{
	int			x;
	t_astree	*head;
	t_astree	*tmp;

	x = -1;
	head = make_tree_node();
	tmp = head;
	//ft_printf("\nStarting make_tree\n");
	while (raw_materials[++x])
	{
		//ft_printf("You are on t_asttoken index %d\n", x);
		tmp->this = raw_materials[x];
		tmp->type = raw_materials[x]->chain->type;
		if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == '&' && raw_materials[x]->chain->type[1] == '&')
			tmp = make_left_branch(tmp/*, 1*/);
		else if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == '|' && raw_materials[x]->chain->type[1] == '|')
			tmp = make_left_branch(tmp/*, 2*/);
		else if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == '|')
			tmp = make_right_branch_pipe(tmp);
		else if (raw_materials[x]->chain && raw_materials[x]->chain->type[0] == ';')
			tmp = make_right_branch_semi_colon(head);
	}
	//ft_printf("\nFinished going through token list\n");
	x = 0;
	print_tree(head, &x);
	return (head);
}
