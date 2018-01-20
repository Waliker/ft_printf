# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 09:16:22 by ndubouil          #+#    #+#              #
#    Updated: 2018/01/18 20:19:13 by ndelest          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries
CC		=	/usr/bin/gcc
AR		=	/usr/bin/ar
RANLIB	=	/usr/bin/ranlib
RM		=	/bin/rm
# Directories
HEADER	=	./
LIB		=	libft/libft.a
# Compilation flags
CFLAGS	=	-Wall -Wextra -Werror
# Files
SRC		=	ft_litoa.c				\
			ft_ssizetoa.c			\
			ft_imtoa.c				\
			ft_printf.c				\
			int_decimaltype.c		\
			ft_ulitoa.c				\
			ft_ullitoa.c			\
			ft_uimtoa.c				\
			unsigned_decimaltype.c	\
			ft_strputlowercase.c	\
			ft_putwchar.c			\
			ft_uitoa_base.c

OBJ		=	$(patsubst %.c,%.o,$(SRC))
HFILES	=	$(HEADER)libftprintf.h
DEBUG	=	-g -fsanitize=address
# Name
NAME	=	libftprintf.a
MAIN	=	mainTest.c
.PHONY: all clean fclean re

all: $(NAME)

$(NAME):	$(OBJ) $(HFILES) Makefile
			@echo "Building $(NAME) ..."
			cp $(LIB) $(NAME)
			@$(AR) rc $(NAME) $(OBJ)
			@$(RANLIB) $(NAME)
			@echo "The library $(NAME) is ready"
			@echo "Compiling main Test ..."

%.o:		%.c $(HFILES)
			$(CC) $(CFLAGS) -c $< -o $@

test:		all
			@$(CC) $(MAIN) $(NAME) -I $(HFILES) -o test

clean:
			@$(RM) -f $(OBJ)

fclean:		clean
			@$(RM) -f $(NAME)

re: 		fclean
			make
