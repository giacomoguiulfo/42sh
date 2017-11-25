/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinfemi <aakin-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:15 by akinfemi          #+#    #+#             */
/*   Updated: 2017/11/22 16:36:19 by akinfemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "get_next_line.h"
#include "libft.h"
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/*
* Bin paths
*/

char    *paths[] = {
    "/usr/bin",
    "/usr/local/bin",
    "/bin",
    "/sbin",
    "/usr/sbin"
};

int     num_of_paths()
{
    return (sizeof(paths) / sizeof(char *));
}

static char *gen_bin_file(char *filename)
{
    int     n_paths = num_of_paths();
    int     i = 0;
    pid_t     pid;
    int     status;
    int     fd;
    int     saved_stdout;

    while (i < n_paths)
    {
        pid = fork();
        if (pid == 0)
        {
            fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
            if (fd < 0)
            {
                printf("error opening\n");
                return (0);
            }
            if (access(paths[i], R_OK) == 0)
            {
                chdir(paths[i]);
                saved_stdout = dup(1);
                dup2(fd, 1);
                close(fd);
                dprintf(1, "%s\n", paths[i]);
                execl("/bin/ls", "ls", NULL);
            }
            else
            {
                printf("Access denied\n");
            }
        }
        if (0 == waitpid(pid, &status, WUNTRACED))
        {
            // close(1);
            dup2(1, saved_stdout);
        }
        i++;
    }
    return (filename);
}

static t_bin *get_bins(void)
{
    char    *filename = gen_bin_file("paths");
    int     rd = 0;
    char    *buffer;
    int     fd;
    t_bin   *bins = NULL;
    t_bin   *temp = NULL;
    char    *path;

    if (access(filename, R_OK) == 0)
    {
        if((fd = open(filename, O_RDONLY)) == -1)
            return (0);
        while((rd = get_next_line(fd, &buffer)) > 0)
        {
            if (buffer && *buffer == '/')
                path = ft_strdup(buffer);
            else
            {
                if (!bins)
                {
                    bins = new_bin(buffer, path);
                    temp = bins;
                }
                else
                {
                    bins->next = new_bin(buffer, path);
                    bins = bins->next;
                }
               
            }
        }
    }
    return (temp);
}

int         main(void)
{
    int     i = 0;
    t_bin  *bins;
    t_bin    *bin;
    int     r;
    t_hash_table *ht = hash_init(10000);
    t_bin *temp;

    srand(time(NULL));
    bins = get_bins();
    if (!bins){
        return (1);
    }
    int j = 0;
    temp = bins;
    while (temp)
    {
        hash_insert(ht, temp->name, temp->path);
        temp = temp->next;
    }

    /*
    * Verify insertion with random searches
    */
    while (i < 10)
	{
        temp = bins;
        r = rand() % ht->capacity;
        while (j++ < r)
            temp = temp->next;
		bin = hash_search(ht, temp->name);
		if (bin != NULL)
			printf("Binary \'%s\', Path %s, R: %d, Search: %s\n", bin->name, bin->path, r, temp->name);
		else
			printf("%s Not found\n", temp->name);
        i++;
        j = 0;
    }
    // ft_bin_lstdel(bins);
    // free_hash(ht);
    return (0);
}