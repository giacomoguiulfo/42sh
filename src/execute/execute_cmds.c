/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _BSD_SOURCE

#include "execute.h"
#include "ft_sh.h"
#include "parser.h"
#include "lexer.h"
#include "builtins.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>

bool	try_pwd(char *binary)
{
	char		cwd_path[MAX_PATH_BIN_SIZE];
	char		*ptr;
	struct stat sb;

	ptr = cwd_path;
	getcwd(ptr, MAX_PATH_BIN_SIZE);
	ft_strcat(cwd_path, "/");
	ft_strcat(cwd_path, binary);
	if ((lstat(cwd_path, &sb)) == -1)
		return (false);
	else if (!check_access(binary, cwd_path))
		return (false);
	else if (!check_reg_file(sb.st_mode))
		return (false);
	return (true);
}

bool	check_access(char *binary, char *path)
{
	if (!((access(path, X_OK)) == 0))
	{
		ft_printf("Lexer: permission denied: %s\n", binary);
		return (false);
	}
	return (true);
}

bool	check_reg_file(mode_t st_mode)
{
	if (!S_ISREG(st_mode))
		return (false);
	return (true);
}

int		get_binary_size(char *binary)
{
	int size;

	size = -1;
	while (ft_isfilename(binary[++size]))
		;
	return (size);
}

bool	try_paths(char *binary, char *path, char *try_this_path)
{
	struct stat sb;
	char		*start;
	char		*end;

	start = path;
	while ((end = ft_strchr(start, ':')) != NULL)
	{
		ft_bzero((void*)try_this_path, MAX_PATH_BIN_SIZE);
		ft_strncpy(try_this_path, start, end - start);
		ft_strcat(try_this_path, "/");
		ft_strcat(try_this_path, binary);
		if ((lstat(try_this_path, &sb)) != -1)
		{
			if (!check_access(binary, try_this_path))
				return (false);
			else if (!check_reg_file(sb.st_mode))
				return (false);
			return (true);
		}
		start = end + 1;
	}
	return (false);
}

bool	check_binary(char *binary, char *path, int *x)
{
	char	bin_name[MAX_PATH_BIN_SIZE];
	char	valid_path[MAX_PATH_BIN_SIZE];
	char	*ptr;
	int		end;

	end = get_binary_size(binary);
	*x = *x + end;
	ptr = valid_path;
	ft_bzero(bin_name, MAX_PATH_BIN_SIZE);
	ft_strncpy(bin_name, binary, end);
	if (try_paths(bin_name, path, ptr))
		return (true);
	else if (try_pwd(binary))
		return (true);
	ft_printf("Lexer: command not found: %s\n", binary);
	return (false);
}

int		msh_run_prog(char *executable, char **args, char **newenvp)
{
 	pid_t	pid;
 	int		status;
 	//char	*full_executable;

 	//full_executable = NULL;
 	ft_printf("Execute: %s\n", executable);
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
void	restore_io(t_shell *shell)
{
	dup2(shell->stdout_backup, 1);
	close(shell->stdout_backup);
	shell->stdout_backup = dup(1);
	dup2(shell->stderr_backup, 2);
	close(shell->stderr_backup);
	shell->stderr_backup = dup(2);
	dup2(shell->stdin_backup, 0);
	close(shell->stdin_backup);
	shell->stdin_backup = dup(0);
}

void	close_fds(t_tokelist *this)
{
	if (this->redir_prefix_fd == -1)
	{
		close(1);
		close(2);
	}
	else if (this->redir_prefix_fd > -1)
		close(this->redir_prefix_fd);
	else if (this->redir_prefix_fd == -2)
		close(1);
	return ;
}

void	redirect_output(t_shell *shell, t_tokelist *this, int opt)
{
	int		suffix_fd;
	int		prefix_fd;
	char	*file;

	file = NULL;
	suffix_fd = -1;
	if (this->redir_prefix_fd == shell->stdin_backup)
		return ;
	if (this->redir_turn_off == true)
	{
		close_fds(this);
		return ;
	}
	if (this->redir_suffix_file)
		file = this->redir_suffix_file;
	if (file)
	{
		suffix_fd = open(file, O_WRONLY | O_CREAT | ((opt) ? O_APPEND : O_TRUNC),
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (this->redir_suffix_fd)
		suffix_fd = this->redir_suffix_fd;
	prefix_fd = 1;
	if (this->redir_prefix_fd > 0)
		prefix_fd = this->redir_prefix_fd;
	dup2(suffix_fd, prefix_fd);
	close(suffix_fd);
}

void	redirect_input(t_tokelist *this)
{
	int		suffix_fd;
	char	*file;

	file = NULL;
	suffix_fd = -2;

	if (this->redir_suffix_file)
		file = ft_hstrndup(this->redir_suffix_file, this->redir_suffix_len);
	if (this->redir_suffix_file)
		suffix_fd = open(file, O_RDONLY);
	if (suffix_fd > 0)
	{
		dup2(suffix_fd, 0);
		close(suffix_fd);
	}
}

void	setup_io(t_shell *shell, t_tokelist **redirs)
{
	int x;

	x = -1;
	while (redirs[++x])
	{
		if (redirs[x]->type[0] == '>' && redirs[x]->type[1] == '>')
			redirect_output(shell, redirs[x], 1);
		else if (redirs[x]->type[0] == '>')
			redirect_output(shell, redirs[x], 0);
		else if (redirs[x]->type[0] == '<')
			redirect_input(redirs[x]);
	}
	ft_printf("-->stdio end!<---\n");
}

void	manage_pipes(t_astree *node)
{
	if (node->this->chain && node->this->chain->type[0] == '|')
	{
		pipe(node->right->pipe_fd);
		dup2(node->right->pipe_fd[1], 1);
		close(node->right->pipe_fd[1]);
	}
	if (node->pipe_fd[0] > -1)
	{
		dup2(node->pipe_fd[0], 0);
		close(node->pipe_fd[0]);
	}
}*/

int		aget_binary_size(char *bin)
{
	int x;

	x = -1;
	while (bin[++x] && ft_isalnum(bin[x]))
		;
	return (x);
}

bool	acheck_builtin(char *binary)
{
	int 	end;
	bool	found;

	found = false;
	end = aget_binary_size(binary);
	if ((ft_strncmp(binary, "cd", 2)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "env", 3)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "history", 7)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "setenv", 6)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "unsetenv", 8)) == 0)
		found = true;
	else if ((ft_strncmp(binary, "exit", 4)) == 0)
		found = true;
    (void)end;
	return (found);
}

int		msh_run_builtin(t_asttoken *this, char **env)
{
	int		ret;

	ret = 0;
	if ((ft_strcmp(this->binary, "cd")) == 0)
		ret = builtin_cd(this->args, env);
	else if ((ft_strcmp(this->binary, "exit")) == 0)
		ret = builtin_exit();
	else if ((ft_strcmp(this->binary, "env")) == 0)
		ret = builtin_exit();
	else if ((ft_strcmp(this->binary, "history")) == 0)
		ret = builtin_history();
	else if ((ft_strcmp(this->binary, "echo")) == 0)
		ret = builtin_echo(this->args, env);
	else if ((ft_strcmp(this->binary, "setenv")) == 0)
		ret = builtin_setenv(this->args, env);
	else if ((ft_strcmp(this->binary, "unsetenv")) == 0)
		ret = builtin_unsetenv(this->args, env);
	return (ret);
}

void	execute_specific_ast_cmds(t_shell *shell, t_astree *node, char *path)
{
	char	*this_path;

	this_path = build_bin_path(path, node->this->binary);
	//if (node->this->redirs && node->this->redirs[0])
	//	setup_io(shell, node->this->redirs);
	//if ((node->this->chain && node->this->chain->type[0] == '|' && node->this->chain->type[1] == '\0') || node->pipe_fd[0] > -1)
	//	manage_pipes(node);
	if (acheck_builtin(node->this->binary))
		node->ret = msh_run_builtins(node->this);
	else
		node->ret = msh_run_prog(this_path, node->this->args, shell->env);
	//restore_io(shell);
	if (node->left && node->type && node->type[0] == '&' && node->ret < 1)
		execute_specific_ast_cmds(shell, node->left, path);
	else if (node->left && node->type && node->type[0] == '|' && node->type[1] == '|' && node->ret > 0)
		execute_specific_ast_cmds(shell, node->left, path);
	if (node->right)
		execute_specific_ast_cmds(shell, node->right, path);
}

void	execute_ast_cmds(t_astree *head)
{
	t_astree	*tmp;
	t_shell		*shell;
	char		*path;

	shell = sh_singleton();
	path = shell->path;
	if (!path)
	{
		ft_printf("NO CMDS!\n");
		return ;
	}
	tmp = head;
	//ft_printf("Starting command execution\n");
	execute_specific_ast_cmds(shell, tmp, path);
}
