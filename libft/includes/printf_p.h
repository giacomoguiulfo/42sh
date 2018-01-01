/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 21:19:02 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/07 13:51:11 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_P_H
# define PRINTF_P_H

# include "libft.h"
# include <stdint.h>
# include <stdarg.h>
# include <stdbool.h>

# define SPECTOTAL 18
# define IS_X(a) (((unsigned)a | 32) - 97 == 23u)
# define IS_O(a) (((unsigned)a | 32) - 97 == 14u)
# define IS_D(a) (((unsigned)a | 32) - 97 == 3u)
# define IS_U(a) (((unsigned)a | 32) - 97 == 20u)
# define IS_XO(a) ((IS_X(a)) || (IS_O(a)))
# define ISLENMOD(a) (a == 'h' || a == 'l' || a == 'j' || a == 'z')

enum	e_lenmod
{
	hh,
	h,
	l,
	ll,
	j,
	z
};

enum	e_flag
{
	LFT = 1 << 0,
	POS = 1 << 1,
	INV = 1 << 2,
	ZER = 1 << 3,
	HTG = 1 << 4
};

typedef struct	s_info
{
	char		flags;
	char		length;
	char		spec;
	int			width;
	int			prec;
	int			pset:1;
}				t_info;

typedef struct	s_convtbl
{
	char spec;
	void (*f)(t_dstr *, t_info *, va_list);
}				t_convtbl;

/*
**	Format Specifier Parse Functions
*/

bool			ft_chk_flags(const char **format, t_info *pfinfo);
bool			ft_chk_width(const char **format, t_info *pfinfo, va_list ap);
bool			ft_chk_prec(const char **format, t_info *pfinfo, va_list ap);
bool			ft_chk_len(const char **format, t_info *pfinfo);

/*
**	Dispatcher Functions
*/

void			ft_get_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_handle_spec(t_dstr *dstr, const char **format,
												t_info *pfinfo, va_list ap);

/*
**  Conversion Functions
*/

void			ft_num_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_str_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_wstr_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_pct_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_chr_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_octal_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_hex_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_uns_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_binary_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_float_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);
void			ft_none_conv(t_dstr *dstr, t_info *pfinfo, va_list ap);

/*
**	Conversion Helpers
*/

void			ft_pad_handle(t_info *pfinfo, char **str);
void			ft_prec_handle(t_info *pfinfo, char **str);
void			ft_prec_nums(t_info *pfinfo, char **str);
int				ft_unicode_b(wchar_t chr);
void			ft_unicode_conv(wchar_t chr, char *str);
char			*ft_null_str(t_info *pfinfo);
uintmax_t		ft_xou_len(char length, va_list ap);
void			ft_handle_xou(char **str, t_info *pfinfo);

/*
**	Helpers/Bonus
*/

void			ft_pfinfo_init(t_info *pfinfo);
bool			ft_pfcolors(t_dstr *dstr, const char **format);

#endif
