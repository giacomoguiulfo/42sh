/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 21:39:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:06:08 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSTR_H
# define DSTR_H

# include <stddef.h>

typedef struct	s_dstr
{
	size_t				len;
	size_t				cap;
	char					*data;
}								t_dstr;

int				ft_dstr_new(t_dstr *dstr, size_t init_cap);
void			ft_dstr_append(t_dstr *dstr, char *newdata);
void			ft_dstr_resize(t_dstr *dstr, size_t min);
void			ft_dstr_nappend(t_dstr *dstr, char *newdata, size_t n);
void			ft_dstr_free(t_dstr *dstr);

#endif
