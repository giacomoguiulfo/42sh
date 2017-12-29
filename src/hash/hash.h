/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:15 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/22 16:36:19 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

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

void				free_hash(t_hash *hash_table);
t_hash_table		*hash_init(int capacity);
int					hash_insert(t_hash_table *ht, char *name, char *path);
char				*hash_search(t_hash_table *ht, char *name);
t_bin				*new_bin(char *name, char *path);

#endif
