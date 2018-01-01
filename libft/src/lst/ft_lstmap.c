/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 22:18:45 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:25:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*ret;

	node = f(lst);
	ret = node;
	while (lst->next)
	{
		lst = lst->next;
		node->next = f(lst);
		node = node->next;
	}
	return (ret);
}
