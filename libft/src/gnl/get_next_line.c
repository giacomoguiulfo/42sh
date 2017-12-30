/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 06:07:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 15:20:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

static int	gnl_read(int fd, char **line, char *content)
{
	char	buf[GNL_BUFF_SIZE + 1];
	char	*tmp;
	char	*ptr;
	int		ret;

	content[0] = '\0';
	while ((ret = read(fd, buf, GNL_BUFF_SIZE)))
	{
		GNL_CHK(ret < 0);
		buf[ret] = '\0';
		if ((ptr = ft_strchr(buf, '\n')) != NULL)
			ft_strcpy(content, ptr + 1);
		if (ptr != NULL)
			*ptr = '\0';
		tmp = *line;
		GNL_CHK((*line = ft_strjoin(*line, buf)) == NULL);
		ft_strdel(&tmp);
		if (ptr)
			return (1);
	}
	if (*line[0] == '\0')
		ft_strdel(line);
	else
		return (1);
	return (0);
}

static int	gnl_cmp_fd(t_gnl *node, int *fd)
{
	return (node->fd - *fd);
}

t_list		**ft_gnl_list(void)
{
	static t_list	*head;

	return (&head);
}

void		ft_gnl_free(void *content, size_t size)
{
	(void)size;
	ft_strdel(&((t_gnl *)content)->file_content);
	free(content);
}

int			get_next_line(const int fd, char **line)
{
	t_list	**head;
	t_list	*tmp;
	t_gnl	new;
	char	*ptr;
	int		ret;

	GNL_CHK(fd < 0 || !line);
	head = ft_gnl_list();
	if ((tmp = ft_lstfind(*head, (void *)&fd, gnl_cmp_fd)) == NULL)
	{
		new.fd = fd;
		new.file_content = ft_strnew(GNL_BUFF_SIZE);
		ft_lstadd(head, ft_lstnew(&new, sizeof(t_gnl)));
		tmp = *head;
	}
	GNL_CHK((*line = ft_strdup(((t_gnl*)tmp->content)->file_content)) == NULL);
	if ((ptr = ft_strchr(*line, '\n')) != NULL)
	{
		ft_strcpy((((t_gnl *)tmp->content)->file_content), ptr + 1);
		*ptr = '\0';
		return (1);
	}
	if ((ret = gnl_read(fd, line, (((t_gnl*)tmp->content)->file_content))) == 0)
		ft_lstdelnode(head, tmp, ft_gnl_free);
	return (ret);
}
