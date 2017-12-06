/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_sh.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
typedef	struct			s_instruction
{
	struct s_command	**commands;
}						t_instruction;
*/

t_instruction	*add_command(t_instruction *vector)
{
	t_instruction	*tmp;
	t_command		**cmds;
	int				x;
	int				y;

	if (!vector)
	{
		x = 1;
		tmp = (t_instruction*)ft_memalloc(sizeof(t_instruction));
		tmp->count = 1;
		tmp->commands = (t_command**)ft_memalloc(sizeof(t_command*) * (x + 1));
		tmp->commands[0] = (t_command*)ft_memalloc(sizeof(t_command));
		tmp->commands[x] = 0;
		return (tmp);
	}
	x = -1;
	while (vector->commands && vector->commands[++x])
		;
	cmds = (t_command**)ft_memalloc(sizeof(t_command*) * (x + 1 + 1));
	cmds[x + 1] = 0;
	y = -1;
	while (++y < x)
		cmds[y] = vector->commands[y];
	cmds[x] = (t_command*)ft_memalloc(sizeof(t_command));
	free(vector->commands);
	vector->commands = cmds;
	vector->count++;
	return (vector);
}

void	tokenize(char *instructions)
{
	t_instruction	*tmp;
	int				x;

	x = -1;
	ft_printf("Inside tokenize\n");
	tmp = add_command(NULL);
	tmp = add_command(tmp);
	tmp = add_command(tmp);
	tmp = add_command(tmp);
	ft_printf("You have created a total of %d commands\n", tmp->count);
	ft_printf("%s\n", instructions);
}

/*
char	*find_path(char *binary, char *path)
{
	struct stat sb;
	char		*try_this_path[MAX_PATH_BIN_SIZE];
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, MAX_PATH_BIN_SIZE);
		ft_strncpy((char*)try_this_path, start, end - start);
		ft_strcat((char*)try_this_path, "/");
		ft_strcat((char*)try_this_path, binary);
		if ((lstat((char*)try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, (char*)try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode))
				return (false);
			return (ft_strdup((const char*)try_this_path));
		}
		start = end + 1;
	}
	return (NULL);
}*/

/*
void	tokenize(char	*instructions)
{
	char	**split;
	char	*path;
	char	*valid;
	pid_t	pid;
	int		status;

	ft_printf("Here are your instructions: %s\n", instructions);
	if (instructions)
		split = ft_strsplit(instructions, ' ');
	else
		return ;
	path = get_path();
	valid = find_path(split[0], path);
	ft_printf("%s\n", valid);
	pid = fork();
	if (pid == 0)
		execve(valid, split, sh_singleton()->env);
	wait(&status);
}*/
