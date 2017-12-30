/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:18:29 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:18:50 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <stddef.h>

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*node;

	if (alst == NULL)
		return ;
	node = *alst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	else
		*alst = new;
}
