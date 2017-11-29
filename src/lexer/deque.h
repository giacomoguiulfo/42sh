/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_dequeNode {
	char *slice;
	t_dequeNode *next;
	t_dequeNode *prev;
};

t_deque {
	t_dequeNode *first;
	t_dequeNode *last;
};

t_deque *dequeInit(void);
void pushFront(t_deque *deque, char *slice);
void pushBack(t_deque *deque, char *slice);
int popFront(t_deque *deque);
int popBack(t_deque *deque);