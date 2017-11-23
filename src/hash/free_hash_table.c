/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:15 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/22 16:36:19 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

/*
* Functions to free binary hash table
*/

/*
* Brief summary
* Delete list
* @param bin: list to be deleted
*/

void            ft_bin_lstdel(t_bin *bin)
{
    t_bin   *temp;

    if (!bin)
        return ;
    while (bin)
    {
        temp = bin->next;
        free(bin->path);
        free(bin->name);
        free(bin);
        bin = temp;
    }
}

/*
* Brief summary
* Free hash
* @param hash_table: hash table to be freed
*/

void            free_hash(t_hash_table *hash_table)
{
    int     i;
    t_bin   *bin;
    
    i = 0;
    while (i < hash_table->capacity)
    {
        bin = hash_table->binaries[i];
        if(bin != 0)
        {
            ft_bin_lstdel(bin);
        }
        i++;
    }
    free(hash_table->binaries);
    free(hash_table);
}