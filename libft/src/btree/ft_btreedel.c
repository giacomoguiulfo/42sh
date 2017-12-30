/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreedel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:52:45 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/01 12:02:03 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	ft_btreedel(t_btree **root, void (*del)(void *, size_t))
{
	if (root && *root && del)
	{
		ft_btreedel((*root)->left, del);
		ft_btreedel((*root)->right, del);
		ft_btreedelone((*root), del);
	}
}
