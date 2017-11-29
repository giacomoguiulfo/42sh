/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

t_deque	*deque_init(void)
{
	t_deque	*deque = (t_deque *)malloc(sizeof(t_deque));
	deque->first = NULL;
	deque->last = NULL;
	return (deque);
}

t_dequeNode *create_node(char *slice)
{
	t_dequeNode *node = (t_dequeNode *)malloc(sizeof(t_dequeNode));
	node->slice = slice;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	pushFront(t_deque *deque, char *slice)
{
	if(!deque)
		return ;
	t_dequeNode *node = create_node(slice);
	node->next = deque->first;
	if (deque->first)
		deque->first->prev = node;
	deque->first = node;
	if (deque->last == NULL)
		deque->last = node;
}

void	pushBack(t_deque *deque, char *slice)
{
	if (!deque)
		return ;
	t_dequeNode *node = create_node(slice);
	node->prev = deque->last;
	if (deque->last)
		deque->last->next = node;
	deque->last = node;
	if (deque->first == NULL)
		deque->first = node;
}

char 	*popFront(t_deque *deque)
{
	char *val;
	if (!deque || !deque->first)
		return (INT_MIN);
	t_dequeNode *node = deque->first;
	deque->first = node->next;
	val = node->slice;
	free(node);
	return(val);
}

char	*popBack(t_deque *deque)
{
	char	*val;
	if (!deque || !deque->last)
		return (INT_MIN);
	t_dequeNode *node = deque->last;
	deque->last = node->prev;
	val = node->slice;
	free(node);
	return (val);
}

char	*peek(t_deque *deque)
{
	if (!deque || !deque->first)
		return (-1);
	return (deque->first->slice);
}