# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/20 11:36:52 by gguiulfo          #+#    #+#              #
#    Updated: 2018/01/16 12:03:02 by gguiulfo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a

# DEBUG		:= 0
DEBUG		:= 1

CC			?= gcc
CFLAGS		+= -std=c99
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -DDEBUG=${DEBUG}
# CFLAGS		+= -Wall -Wextra -Werror -Wfloat-equal -Wundef
# CFLAGS		+= -Wpointer-arith -Wunreachable-code -Winit-self
# CFLAGS		+= -O3 -march=native -pipe -flto

# DEBUG		:= 0
# ifeq ($(DEBUG),1)
# CFLAGS		+= -g -fsanitize=address
# endif

ifndef VERBOSE
MAKEFLAGS	+= --no-print-directory
endif

ARR :=						\
ft_arr_free 				\
ft_arr_remove_nth
BTREE :=					\
ft_btreenew
CHR :=						\
ft_putnchar_fd 				\
ft_putchar_fd 				\
ft_putchar 					\
ft_getchar					\
ft_isalnum 					\
ft_isalpha 					\
ft_isascii 					\
ft_isdigit 					\
ft_isprint 					\
ft_isspace 					\
ft_islower 					\
ft_isupper 					\
ft_tolower 					\
ft_toupper
DARR :=						\
ft_darr_clear				\
ft_darr_contract			\
ft_darr_destroy				\
ft_darr_expand				\
ft_darr_get					\
ft_darr_init				\
ft_darr_kill				\
ft_darr_new					\
ft_darr_pop					\
ft_darr_push				\
ft_darr_remove				\
ft_darr_resize				\
ft_darr_reverse				\
ft_darr_set
DSTR :=						\
ft_dstr_append				\
ft_dstr_free				\
ft_dstr_nappend				\
ft_dstr_new					\
ft_dstr_resize
ERR :=						\
ft_perror					\
ft_error_exit			\
ft_usage
OPTS :=						\
ft_opts_getlong				\
ft_opts_getshort			\
ft_opts_handle				\
ft_opts_help				\
ft_opts_parse				\
ft_opts_suggest				\
ft_opts_usage				\
ft_opts
HEAP :=						\
ft_heap_singleton 			\
ft_heap_clear 				\
ft_hfree 					\
ft_hmalloc 					\
ft_hmemalloc 				\
ft_hrealloc					\
ft_hstrdup					\
ft_hstrndup
PRINTF_P := 				\
ft_pf_chr_conv 				\
ft_pf_float_conv 			\
ft_pf_fmt_parse 			\
ft_pf_handle_spec	 		\
ft_pf_num_conv 				\
ft_pf_bonus 				\
ft_pf_handlers 				\
ft_pf_str_conv 				\
ft_pf_wstr_conv 			\
ft_pf_xou_conv
PRINTF :=					\
ft_printf 					\
ft_printf_more
SORT :=						\
ft_qsort
FT_TERM :=					\
ft_clrscreen 				\
ft_cursor_goto 				\
ft_get_win_size	 			\
ft_highlight 				\
ft_termcmd 					\
ft_underline
GNL :=						\
get_next_line
LST	:=						\
ft_lst						\
ft_lstadd 					\
ft_lstappend				\
ft_lstdel_if				\
ft_lstdel 					\
ft_lstdelnode 				\
ft_lstdelone 				\
ft_lstfind 					\
ft_lstfree					\
ft_lstiter 					\
ft_lstlast					\
ft_lstmap 					\
ft_lstnew					\
ft_lstreverse				\
ft_lstsize
MEM :=						\
ft_addrcmp					\
ft_bzero 					\
ft_crealloc					\
ft_memccpy 					\
ft_memchr 					\
ft_memcmp 					\
ft_memcpy 					\
ft_memmove 					\
ft_memset 					\
ft_memalloc 				\
ft_memdel 					\
ft_realloc					\
ft_memrealloc 				\
ft_swap
NBR :=						\
ft_atoi 					\
ft_atoi_base 				\
ft_imaxtoa 					\
ft_is_sort 					\
ft_itoa_base 				\
ft_itoa 					\
ft_nblen 					\
ft_putnbr_fd 				\
ft_putnbr 					\
ft_range 					\
ft_uimaxtoa_base			\
ft_pow 						\
ft_sqrtf
SSTR :=						\
ft_sstrdel					\
ft_sstrdelone				\
ft_sstrdup					\
ft_sstrlen					\
ft_sstrpush					\
ft_sstrputs
STR :=						\
ft_basename					\
ft_countwords 				\
ft_findchr 					\
ft_free_sstr 				\
ft_insrt_to_str 			\
ft_putendl_fd 				\
ft_putendl 					\
ft_putstr_fd 				\
ft_putstr 					\
ft_str_tolower				\
ft_strcat 					\
ft_strchr 					\
ft_strclr					\
ft_strcmp 					\
ft_strcpy 					\
ft_strdel 					\
ft_strdup 					\
ft_strequ 					\
ft_stris					\
ft_striter 					\
ft_striteri 				\
ft_strjoin 					\
ft_strlcat 					\
ft_strlen 					\
ft_strlenchr				\
ft_strmap 					\
ft_strmapi 					\
ft_strncat 					\
ft_strncmp 					\
ft_strncpy 					\
ft_strndup 					\
ft_strnequ 					\
ft_strnew 					\
ft_strnstr 					\
ft_strpbrk					\
ft_strrchr 					\
ft_strrev 					\
ft_strsep					\
ft_strsplit 				\
ft_strstr					\
ft_strsub 					\
ft_strtrim
SYS :=						\
ft_getenv					\
ft_isdir					\
ft_unixcase

SRC_BASE	:=												\
$(addprefix arr/, $(ARR))									\
$(addprefix btree/, $(BTREE))								\
$(addprefix chr/, $(CHR))									\
$(addprefix darr/, $(DARR))									\
$(addprefix dstr/, $(DSTR))									\
$(addprefix err/, $(ERR))									\
$(addprefix opts/, $(OPTS))									\
$(addprefix ft_term/, $(FT_TERM))							\
$(addprefix gnl/, $(GNL))									\
$(addprefix heap/, $(HEAP))									\
$(addprefix lst/, $(LST))									\
$(addprefix mem/, $(MEM))									\
$(addprefix nbr/, $(NBR))									\
$(addprefix printf/, $(PRINTF_P))							\
$(addprefix printf/, $(PRINTF))								\
$(addprefix sort/, $(SORT))									\
$(addprefix sstr/, $(SSTR))									\
$(addprefix str/, $(STR))									\
$(addprefix sys/, $(SYS))

INC_DIR		:= includes/
OBJ_DIR		:= obj/
SRC_DIR		:= src/
SRC				:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_BASE)))
OBJ				:= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))
INC_BASE	:= $(wildcard $(INC_DIR)*.h)
SHELL			:= /bin/bash
BASENAME  := `basename -s .a $(NAME)`
LEN_NAME	= `printf "%s" $(NAME) | wc -c`
DELTA			= $$(echo "$$(tput cols)-31-$(LEN_NAME)" | bc)
NB				= $(words $(SRC_BASE))
INDEX			= 0

all:
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "\r\033[38;5;15m✓ make   $(BASENAME)\033[0m\033[K\n";

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJ))

$(OBJ_DIR)%.o:$(SRC_DIR)%.c Makefile | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(141 105 69 33 39 45 51 87 123 159 195 231 15); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]:%2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙ %*.*s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:
	@if [ -e $(OBJ_DIR) ]; \
	then \
		rm -rf $(OBJ_DIR); \
		printf "\r\033[38;5;219m✗ clean  $(BASENAME)\033[0m\033[K\n"; \
	fi;

fclean: clean
	@if [ -e $(NAME) ]; \
	then \
		rm -rf $(NAME); \
		printf "\r\033[38;5;33m✗ fclean $(BASENAME)\033[0m\033[K\n"; \
	fi;

re: fclean all

.PHONY: all clean fclean re

-include $(OBJ:.o=.d)
