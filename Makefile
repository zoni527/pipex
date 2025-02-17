# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:58:04 by jvarila           #+#    #+#              #
#    Updated: 2025/02/09 10:50:30 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
DEBUGFLAGS	:= -g
#------------------------------------------------------------------------------#
SRCDIR		:= ./
INCDIR		:= ./
OBJDIR		:= ./obj
LIBFTDIR	:= ./libft
#------------------------------------------------------------------------------#
SRC	:=	pipex.c					\
		data_setup_cleanup_and_errors.c		\
		prepare_bins.c				\
		prepare_bins_utils.c			\
		forks_and_children.c			\
		infile_and_outfile.c			\
		pipe_redirection_and_bin_check.c

OBJ		:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
#------------------------------------------------------------------------------#
LIBFT		:= $(LIBFTDIR)/libft.a
LIBFTH		:= $(LIBFTDIR)/libft.h
PPXH		:= $(INCDIR)/pipex.h
INC		:= -I $(LIBFTDIR) -I $(INCDIR)
#------------------------------------------------------------------------------#
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT) $(LIBFTH) $(PPXH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INC) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(PPXH)
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make all -C $(LIBFTDIR)

clean:
	make clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all
#------------------------------------------------------------------------------#
debug: CFLAGS += $(DEBUGFLAGS)
debug: fclean libftdebug all

libftdebug:
	make debug -C $(LIBFTDIR)
#------------------------------------------------------------------------------#
.PHONY: all clean fclean re debug libftdebug
#------------------------------------------------------------------------------#
