/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
#define REDIR_H

int         redir_gt(int new_fd, char *filename);
int         redir_ggt(int new_fd, char *filename);
int         redir_lt(int new_fd, char *filename);

#endif