/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 22:15:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:23:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	f(lst);
	while (lst->next)
	{
		lst = lst->next;
		f(lst);
	}
}
