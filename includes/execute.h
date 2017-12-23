#ifndef EXECUTE_H
# define EXECUTE_H

#include "ft_sh.h"
#include "lexer.h"

void	execute_ast_cmds(t_astree *head);

bool	check_reg_file(mode_t st_mode);
bool	check_access(char *binary, char *path);

#endif