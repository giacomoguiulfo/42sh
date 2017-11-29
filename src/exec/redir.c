/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int         redir_gt(int new_fd, char *filename)
{
    int     old_fd;

    old_fd = open(filename, O_WRONLY | O_CREAT, 0666);
    if (old_fd == -1)
        return (0);
    dup2(old_fd, new_fd);
    close(old_fd);
    return (1);
}

int         redir_ggt(int new_fd, char *filename)
{
    int     old_fd;
    
    old_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (old_fd == -1)
        return (0);
    dup2(old_fd, new_fd);
    close(old_fd);
    return (1);
}

int         redir_lt(int new_fd, char *filename)
{
    int     old_fd;

    old_fd = open(filename, O_WRONLY | O_CREAT, 0666);
    if (old_fd == -1)
        return (0);
    dup2(old_fd, new_fd);
    close(old_fd);
    return (1);
}