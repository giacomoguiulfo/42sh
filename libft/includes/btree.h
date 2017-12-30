/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 01:41:49 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:54:33 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "libft.h"

typedef struct s_btree	t_btree;

struct		s_btree
{
	void	*content;
	size_t	content_size;
	t_btree	*left;
	t_btree	*right;
};

t_btree		*ft_btreenew(void const *content, size_t content_size);

#endif
