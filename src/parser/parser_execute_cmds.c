/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execute_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/28 11:54:57 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "parser.h"
#include "lexer.h"
#include "ft_sh.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>

int		msh_run_prog(char *executable, char **args, char **newenvp)
{
 	pid_t	pid;
 	int		status;

 	pid = fork();
 	if (pid == 0)
	{
		if (execve(executable, args, newenvp) == -1)
 		{
			ft_dprintf(2, "msh: permission denied: %s\n", executable);
		}
		exit(EXIT_FAILURE);
 	}
 	else if (pid < 0)
 	{
		ft_dprintf(2, "msh: unable to fork process: %d\n", pid);
		exit(EXIT_FAILURE);
 	}
 	wait(&status);
 	return (status);
}

char	*build_bin_path(char *path, char *binary)
{
	char		*start;
	char		*end;
	char		buff[MAX_PATH_BIN_SIZE];
	struct stat sb;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)buff, MAX_PATH_BIN_SIZE);
		ft_strncpy(buff, start, end - start);
		ft_strcat(buff, "/");
		ft_strcat(buff, binary);
		if ((lstat(buff, &sb)) != -1)
		{
			if (!check_access(binary, buff))
				return (NULL);
			else if (!check_reg_file(sb.st_mode))
				return (NULL);
			return (ft_hstrdup(buff));
		}
		start = end + 1;
	}
	return (NULL);
}

/*
typedef struct			s_asttoken
{
	char				*binary;
	char				**args;
	struct s_tokelist	**redirs;
	struct s_tokelist	*chain;
}						t_asttoken;

typedef struct			s_astree
{
	int					ret;
	struct s_asttoken	*this;
	struct s_astree		*left;
	struct s_astree		*right;	
}						t_astree;

typedef struct			s_tokelist
{
	void				*content;
	size_t				len;
	char				type[3];
	int					redir_prefix_fd;
	char				*redir_suffix_file;
	int					redir_suffix_len;
	int					redir_suffix_fd;
	struct s_tokelist	*next;
}						t_tokelist;
*/

void	redirect_output(t_tokelist *this, int opt)
{
	ft_printf("redir type: %s, opt: %d\n", this->type, opt);
}

void	setup_io(t_shell *shell, t_tokelist **redirs)
{
	int x;

	x = -1;
	ft_printf("~stdio backups:\n");
	ft_printf("in: %d, out: %d, err: %d\n", shell->stdin_backup, shell->stdout_backup, shell->stderr_backup);
	while (redirs[++x])
	{
		ft_printf("redir index %d\n", x);
		if (redirs[x]->type[0] == '>' && redirs[x]->type[1] == '>')
			redirect_output(redirs[x], 2);
		else if (redirs[x]->type[0] == '>')
			redirect_output(redirs[x], 1);
	}
}

void	execute_specific_ast_cmds(t_shell *shell, t_astree *node, char *path)
{
	char	*this_path;

	this_path = build_bin_path(path, node->this->binary);
	node->ret = msh_run_prog(this_path, node->this->args, shell->env);
	ft_printf("Just executed %s with return %d\n", this_path, node->ret);
	ft_printf("File redirection info:\n");
	if (node->this->redirs && node->this->redirs[0])
	{
		setup_io(shell, node->this->redirs);
	}
	else
		ft_printf("No redirections found\n");
	if (node->left && node->type && node->type[0] == '&' && node->ret < 1)
	{
		ft_printf("starting new cmd\n");
		execute_specific_ast_cmds(shell, node->left, path);
	}
	else if (node->left && node->type && node->type[0] == '|' && node->type[1] == '|' && node->ret > 0)
	{
		ft_printf("starting new cmd\n");
		execute_specific_ast_cmds(shell, node->left, path);
	}
	if (node->right)
	{
		ft_printf("starting new cmd\n");
		execute_specific_ast_cmds(shell, node->right, path);
	}
}

void	execute_ast_cmds(t_astree *head)
{
	t_astree	*tmp;
	t_shell		*shell;
	char		*path;

	shell = sh_singleton();
	path = get_path();
	tmp = head;
	ft_printf("Starting command execution\n");
	execute_specific_ast_cmds(shell, tmp, path);
}

























