/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 01:53:12 by rschramm          #+#    #+#             */
/*   Updated: 2017/12/16 20:31:37 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <fcntl.h>

bool	close_fds(t_tokelist *this)
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
	return (true);
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
	if (this->redir_turn_off == true && close_fds(this))
		return ;
	if (this->redir_suffix_file)
		file = this->redir_suffix_file;
	if (file)
		suffix_fd = open(file, O_WRONLY | O_CREAT | ((opt) ? O_APPEND :
			O_TRUNC), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
		file = this->redir_suffix_file;
	if (this->redir_suffix_file)
		suffix_fd = open(file, O_RDONLY);
	if (suffix_fd > -1)
	{
		dup2(suffix_fd, 0);
		close(suffix_fd);
	}
}

void	setup_io(t_shell *shell, t_tokelist **redirs)
{
	int x;

	ft_printf("inside setupio\n");
	if (!redirs)
		return ;
	x = -1;
	ft_printf("inside setup io\n");
	while (redirs[++x])
	{
		if (redirs[x]->type[0] == '>' && redirs[x]->type[1] == '>')
			redirect_output(shell, redirs[x], 1);
		else if (redirs[x]->type[0] == '>')
			redirect_output(shell, redirs[x], 0);
		else if (redirs[x]->type[0] == '<')
			redirect_input(redirs[x]);
	}
}
