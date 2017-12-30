/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 01:30:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:48:46 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARR_H
# define DARR_H

# include <stddef.h>

# define DARR_EXPAND_RATE 300
# define FT_DARR_LAST(a) ((a)->content[(a)->len - 1])
# define FT_DARR_FIRST(a) ((a)->content[0])
# define FT_DARR_LEN(a) ((a)->len)
# define FT_DARR_COUNT(a) FT_DARR_LEN(a)
# define FT_DARR_SIZE(a) ((a)->size)

typedef int	(*t_sortcast) (const void *a, const void *b);

typedef	struct		s_darr
{
	int				len;
	int				size;
	size_t			expand_rate;
	size_t			content_size;
	void			**content;
}					t_darr;

void				ft_darr_clear(t_darr *array);
int					ft_darr_contract(t_darr *array);
void				ft_darr_destroy(t_darr *array);
int					ft_darr_expand(t_darr *array);
void				*ft_darr_get(t_darr *array, int i);
t_darr				*ft_darr_init(size_t content_size, size_t initial_size);
void				ft_darr_kill(t_darr *array);
void				*ft_darr_new(t_darr *array);
void				*ft_darr_pop(t_darr *array);
int					ft_darr_push(t_darr *array, void *el);
void				*ft_darr_remove(t_darr *array, int i);
int					ft_darr_resize(t_darr *array, size_t newsize);
void				ft_darr_reverse(t_darr *array);
void				ft_darr_set(t_darr *array, int i, void *el);

#endif
