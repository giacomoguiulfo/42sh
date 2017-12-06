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

int		ft_iscmd_delim(char *c)
{
	if (c[0] == '|' && c[1] == '|')
		return (1);
	else if (c[0] == '&' && c[1] == '&')
		return (2);
	else if (c[0] == '|')
		return (3);
	else if (c[0] == '&')
		return (4);
	else if (c[0] == ';')
		return (5);
	return (0);
}

typedef struct	s_cmd_extractor
{
	bool		found_bin;
	char		*start;
	char		*end;
	char		*bin_start;
	char		*bin_end;
	char		buff[8192];
	int			x;
}				t_cmd_extractor;

t_instruction	*tokenize_constructor(t_cmd_extractor *help, char *inst)
{
	t_instruction *tmp;

	tmp = NULL;
	help->x = -1;
	help->end = NULL;
	help->start = inst;
	ft_bzero((void*)help->buff, 8192);
	return (tmp);
}

bool	ft_ismetachar(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '"' ||
		c == '`' || c == '>' || c == '<' || c == ' ' ||
		c == 39)
		return (true);
	return (false);
}

bool	fast_forward(t_cmd_extractor *help, char *str, int x, int opt)
{
	char c;

	if (opt == 0)
	{
		c = str[x];
		help->bin_start = str + x;
		while (str[++x] != c)
			;
		help->bin_end = str + x;
	}
	else
	{
		help->bin_start = str + x;
		while (!ft_ismetachar(str[++x]))
			;
		help->bin_end = str + x;
	}
	return (true);
}

bool	find_binary(t_cmd_extractor *help, char *str)
{
	int		x;

	x = -1;
	ft_putstr("Inside find binary\n");
	while (str[++x])
	{
		if (ft_isquote(str[x]))
			return (fast_forward(help, str, x, 0));
		else if (ft_isalnum(str[x]))
			return (fast_forward(help, str, x, 1));
	}
	return (false);
}

void	extract_cmd(t_cmd_extractor help, t_instruction *tmp)
{
	t_command *this;

	if (!find_binary(&help, help.buff))
		return ;
	this = (t_command*)ft_memalloc(sizeof(t_command));
	this->binary = ft_strndup(help.bin_start, help.bin_end - help.bin_start);
	ft_printf("binary: %s\n", this->binary);
	free(this->binary);
	tmp = NULL;
}

void	tokenize(char *instructions)
{
	t_instruction	*tmp;
	t_cmd_extractor help;

	tmp = tokenize_constructor(&help, instructions);
	while (instructions[++help.x])
	{
		if (ft_iscmd_delim(instructions + help.x))
		{
			help.end = instructions + help.x;
			ft_strncpy(help.buff, help.start, help.end - help.start);
			extract_cmd(help, tmp);
			help.start = instructions + help.x + 1;
			help.end = NULL;
		}
	}
	help.end = instructions + help.x;
	ft_strncpy(help.buff, help.start, help.end - help.start);
	extract_cmd(help, tmp);
	if (tmp)
		ft_printf("token count is: %zu\n", tmp->count);
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
