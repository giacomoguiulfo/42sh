/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 08:58:55 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 11:51:26 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"

extern char		**g_argv;

void	ft_error_exit(const char *str);
int		ft_perror(char *name);
void	ft_usage(char const *name, char const *str);

#endif
