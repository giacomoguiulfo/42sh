/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 21:35:43 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:54:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSTR_H
# define SSTR_H

void	ft_sstrdel(char ***sstr);
void	ft_sstrdelone(char **sstr, int index);
char	**ft_sstrdup(char **sstr);
size_t	ft_sstrlen(char *const sstr[]);
char	**ft_sstrpush(char **sstr, char *str);
void	ft_sstrputs(char **sstr);

#endif
