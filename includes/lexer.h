/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:03:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/28 17:06:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_sh.h"

enum e_lexstate
{
	DEFAULT,
	PARENTHESIS,
	HEREDOC,
	NEWLINE,
	DELIM,
	SEPARATOR,
	WORD,
	NUMBER,
	LESS,
	GREATER,
	QUOTE,
	DQUOTE,
	BQUOTE,
	BACKSLASH,
	CURLY_BRACKETS,
	EOF
};

bool	lexer(char *cmds);

#endif
