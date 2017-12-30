/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:53:51 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:50:30 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_H
# define ARR_H

# include <stddef.h>

void	ft_arr_remove_nth(int nth, void *array, size_t size, int len);
void	ft_arr_free(void **d_arr, int rows);

#endif
