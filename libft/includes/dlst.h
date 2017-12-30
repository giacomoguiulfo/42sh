/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 06:36:00 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:47:34 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLST_H
# define DLST_H

typedef struct s_dlst	t_dlst;

struct		s_dlst
{
	void	*content;
	size_t	content_size;
	t_dlst	*next;
	t_dlst	*prev;
};

#endif
