/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:15 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/22 16:36:19 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Brief summary
* Basic hash function
* @param name: string to hash
* @return: hash result
*/

size_t				hash(char *name)
{
	size_t			res;
	int				i;

	res = 0;
	i = 1;
	while(name && *name && i)
	{
		res += *name * ft_pow(10 , i);
		name++;
	}
	return (res);
}

/*
* Brief summary
* Create new binary entry
* @param name: binary name
* @param name: binary path
* @return: binary entry
*/

t_bin				*new_bin(char *name, char *path)
{
	t_bin			*bin;

	bin = (t_bin *)malloc(sizeof(t_bin));
	bin->name = name;
	bin->path = path;
	bin->next = NULL;
	return (bin);
}

/*
* Brief summary
* Create hash table
* @param capacity: array size
* @return: new hash_table
*/

t_hash_table		*hash_init(int capacity)
{
	t_hash_table	*hash_table;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	hash_table->capacity = capacity;
	hash_table->binaries = (t_bin **)ft_memalloc(capacity, sizeof(t_bin *));
	return (hash_table);
}

/*
* Brief summary
* Insert binary to hash_table
* @param ht: existing hash table (hashInit has been called)
* @oaram name: binary name
* @oaram name: binary path
* @return: 1 upon success and 0 upon failure
*/

int					hash_insert(t_hash_table *ht, char *name, char *path)
{
	size_t		index;
	t_bin		*head;

	if(!ht)
		return (-1);
	index = hash(name) % ht->capacity;
	head = ht->binaries[index];
	if (head == 0)
	{
		head = new_bin(name, path);
		ht->binaries[index] = head;
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new_bin(name, path);
	}
	return (1);
}

/*
* Brief summary
* Search for binary in hash_table
* @param ht: existing hash table (hashInit has been called)
* @param name: binary name
* @return : binary path upon success and NULL if not found
*/

char				*hash_search(t_hash_table *ht, char *name)
{
	size_t		index;
	t_bin		*bin;

	if(!ht)
		return (0);
	index = hash(name) % ht->capacity;
	bin = ht->binaries[index];
	if (!bin)
		return (0);
	if (strcmp(bin->name, name) == 0)
		return (bin->path);
	else
	{
		while (bin)
		{
			if (strcmp(bin->name, name) == 0)
				return (bin->path);
			bin = bin->next;
		}
	}
	return (0);
}