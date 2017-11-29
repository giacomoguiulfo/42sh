/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <unistd.h>
#include <stdlib.h>

int         exec_pipe(char *cmd1, char **args1, char *cmd2, char **args2)
{
    int     fildes[2];
    int     pid;

    pipe(fildes);
    if ((pid = fork()) == 0)
    {
        dup2(fildes[WRITE_END], STDOUT_FILENO);
        close(fildes[READ_END]);
        execve(cmd1, args1, NULL);
    }
    else if (pid == -1)
    {
        close(fildes[READ_END]);
        close(fildes[WRITE_END]);
        return (0);
    }
    dup2(fildes[READ_END], STDIN_FILENO);
    close(fildes[WRITE_END]);
    wait(NULL);
    execve(cmd2, args2, NULL);
    return (1);
}