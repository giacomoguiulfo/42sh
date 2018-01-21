/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:04:59 by gguiulfo          #+#    #+#             */
/*   Updated: 2018/01/11 17:12:08 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ft_sh.h"
# include "lexer.h"
# include "parser.h"

typedef struct	s_here
{
	char		*new_instr;
	char		*prompt;
	char		*safe_word;
	char		buff[4092];
	int			ret;
}				t_here;

void			check_pipes(t_astree *node);
void			execute_ast_cmds(t_astree *head);
t_astree		*piped_execution(t_shell *shell, t_astree *node, char *this_path, char *path);
void			redirect_heredoc(t_tokelist *redir);
void			restore_io(t_shell *shell);
void			setup_io(t_shell *shell, t_tokelist **redirs);

bool			try_without_path(char *test);
int				msh_run_prog(char *executable, char **args, char **newenvp);
char			*build_bin_path(char *path, char *binary);

bool			check_access(char *path);
bool			check_builtin(char *binary);
bool			check_reg_file(mode_t st_mode);
t_builtin		*msh_run_builtin(char *name);

#endif
