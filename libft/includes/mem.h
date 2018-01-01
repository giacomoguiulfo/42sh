/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 20:08:44 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/30 08:18:02 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

int		ft_addrcmp(void *a, void *b);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_realloc(void *ptr, size_t src_size, size_t new_size);
void	*ft_memrealloc(void *ptr, size_t src_size, size_t new_size);
void	ft_swap(void *a, void *b, size_t s);

void	ft_bzero(void *s, size_t n);
void	*ft_crealloc(void *ptr, int size);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);

#endif
