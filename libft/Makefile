# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:58:04 by jvarila           #+#    #+#              #
#    Updated: 2024/12/19 11:27:15 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR		:= ar -crs
DEBUGFLAGS	:= -g

HF		:= libft.h

SRC :=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c	\
	ft_isprint.c	ft_strlen.c	ft_memset.c	ft_bzero.c	\
	ft_memcpy.c	ft_memmove.c	ft_strlcpy.c	ft_strlcat.c	\
	ft_toupper.c	ft_tolower.c	ft_strchr.c	ft_strrchr.c	\
	ft_strncmp.c	ft_memchr.c	ft_memcmp.c	ft_strnstr.c	\
	ft_atoi.c	ft_calloc.c	ft_strdup.c	ft_substr.c	\
	ft_strjoin.c	ft_strtrim.c	ft_split.c	ft_itoa.c	\
	ft_strmapi.c	ft_striteri.c	ft_putchar_fd.c	ft_putstr_fd.c	\
	ft_putendl_fd.c	ft_putnbr_fd.c	\
	ft_lstnew.c	ft_lstadd_front.c	ft_lstsize.c	\
	ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c	\
	ft_lstiter.c	ft_lstmap.c		ft_lstclear.c	\
	ft_putstr.c	ft_putchar.c	ft_putendl.c	ft_putnbr.c	\
	ft_putnbr_base.c	\
	ft_longtoa.c	ft_hextoa.c	ft_utoa.c	ft_ulongtoa.c	\
	ft_int_digits.c	ft_ulong_digits.c	ft_uint_digits.c	\
	ft_ulong_digits.c	ft_ulong_hex_digits.c	\
	free_ptr_return_int.c	\
	free_null_ended_array.c	\
	free_null_ended_array_return_null.c	\
	free_null_ended_array_return_int.c	\
	write_error_return_int.c	\
	write_error_return_null.c	\
	ft_printf.c	handle_c.c	handle_s.c	handle_p.c	\
	handle_d.c	handle_i.c	handle_u.c	\
	handle_hex_lowercase.c	handle_hex_uppercase.c	\
	get_next_line.c	get_next_line_utils.c	\
	isnumstr.c	\
	ft_atol.c	\
	word_count.c	\
	skip_whitespace.c	skip_char.c	\
	larger_int.c	smaller_int.c	\
	first_int_larger.c	first_int_smaller.c	\
	ft_iabs.c	\
	valid_multinumberstring.c	\
	ft_islower.c	ft_isupper.c	\
	contains_duplicate_char.c	char_index.c	\
	valid_hex_string.c	atou_base.c	atohex.c


OBJ	:= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HF)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

.PHONY: clean fclean re debug
