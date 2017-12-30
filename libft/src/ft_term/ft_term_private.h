/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 18:05:32 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/29 18:16:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERM_PRIVATE_H
# define FT_TERM_PRIVATE_H

void	ft_cursor_goto(int x, int y);
void	ft_termcmd(char *str);
void	ft_get_win_size(int *x, int *y);

#endif
