/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:23:00 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/28 09:23:02 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

/*
* Function to split input
*/

char        *get_slice(t_deque *deque, char *str)
{
    char    *res;
    char    *temp;
    int     n_bytes;

    temp = popFront(deque_quotes);
    n_bytes = temp - str;
    res = (char *)malloc(sizeof(char) * n_bytes + 1);
    memcpy(res, temp, n_bytes);
    res[n_bytes] = '\0';
    return (res);
}

int         has_inhibitor(char *str)
{
    while(str && *str)
    {
        if (*str == "\\" || *str == "\'" || *str == "\"")
            return (1);
    }
    return (0);
}

t_deque        *split(char *str)
{
    t_deque	*deque_quotes;
    t_deque *deque_slices;
    char    *temp;

    if (!str)
        return (NULL);
    deque_quotes = deque_init();
    deque_slices= deque_init();
    temp = str;
    if (!has_inhibitor(temp))
    {
        pushBack(deque_slices, temp);
        return (deque_slices);
    }
    while(temp)
    {
        if (*temp == "\"" || *temp == "\'")
        {
            if (!peek(deque_quotes) || *(peek(deque_quotes)) != *temp)
                pushFront(deque_quotes, temp);
            else if (peek(deque_quotes) && *(peek(deque_quotes)) == *temp)
                pushBack(deque_slices, get_slice(deque_quotes, temp));
        }
        else if(*temp == "\\")
            temp = temp + 2;
    }
    //set state depending on the quote type
    if (is_empty(deque_quotes))
        return (deque_slices);
    return (NULL);
}