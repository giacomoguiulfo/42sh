/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:24:57 by giacomo           #+#    #+#             */
/*   Updated: 2017/11/28 05:57:15 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int builtin_exit()
{
    // TODO: Clean up stuff before exiting
    exit(EXIT_SUCCESS);
    return (0);
}
