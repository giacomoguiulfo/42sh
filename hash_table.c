/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <femi@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:15 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/22 16:36:19 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct		s_bin
{
	char			*name;
	char			*path;
	struct s_bin	*next;
}					t_bin;

typedef struct		s_hash_table
{
	struct s_bin	**binaries;
	int				capacity;
}					t_hash_table;

size_t				hash(char *name)
{
	size_t			res;

	res = 0;
	while(name && *name)
	{
		res += *name * 31;
		name++;
	}
	return (res);
}

t_bin				*new_bin(char *name, char *path)
{
	t_bin			*bin;

	bin = (t_bin *)malloc(sizeof(t_bin));
	bin->name = name;
	bin->path = path;
	bin->next = NULL;
	return (bin);
}

t_hash_table		*hashInit(int capacity)
{
	t_hash_table	*hash_table;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	hash_table->capacity = capacity;
	hash_table->binaries = (t_bin **)calloc(capacity, sizeof(t_bin *));
	return (hash_table);
}

int					hashInsert(t_hash_table *ht, char *name, char *path)
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

char				*hashSearch(t_hash_table *ht, char *name)
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