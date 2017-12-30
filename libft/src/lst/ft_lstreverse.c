/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 06:09:27 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/07 13:46:10 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

t_list	*ft_lstreverse(t_list **head)
{
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	if (head)
	{
		while (*head)
		{
			next = (*head)->next;
			(*head)->next = prev;
			prev = *head;
			*head = next;
		}
		*head = prev;
	}
	return (prev);
}
