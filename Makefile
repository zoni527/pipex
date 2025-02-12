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
SRC	:=	pipex.c			\
		prepare_bins.c

OBJ		:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
#------------------------------------------------------------------------------#
BNAME		:= pipex_bonus
BSRCDIR		:= ./
BOBJDIR		:= ./obj_bonus

BSRC :=	pipex_bonus.c

BOBJ	:= $(addprefix $(BOBJDIR)/, $(BSRC:.c=.o))
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
	rm -rf $(BOBJDIR)

fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -f $(NAME)
	rm -f $(BNAME)

re: fclean all
#------------------------------------------------------------------------------#
bonus: $(BNAME)

$(BNAME): $(BOBJDIR) $(BOBJ) $(LIBFT) $(LIBFTH) $(PPXH)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) $(INC) -o $@

$(BOBJDIR)/%.o: $(BSRCDIR)/%.c $(PPXH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(BOBJDIR):
	mkdir -p $(BOBJDIR)
#------------------------------------------------------------------------------#
debug: CFLAGS += $(DEBUGFLAGS)
debug: fclean libftdebug all

libftdebug:
	make debug -C $(LIBFTDIR)
#------------------------------------------------------------------------------#
.PHONY: all clean fclean re phony debug libftdebug bonus
#------------------------------------------------------------------------------#
