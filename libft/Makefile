# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/03 21:44:29 by mbellaic          #+#    #+#              #
#    Updated: 2017/01/28 23:33:13 by mbellaic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		SHELL = /bin/zsh
else
		SHELL = /bin/bash
endif

CC=cc
CFLAGS=-Wall -Wextra -Werror
SRC = 	ft_strlen.c \
	  	ft_strdup.c \
	  	ft_strcpy.c \
	  	ft_strncpy.c \
	  	ft_strcat.c \
	  	ft_strlcat.c \
	  	ft_strchr.c \
	  	ft_strrchr.c \
	  	ft_strstr.c \
	  	ft_strstr.c \
	 	ft_strnstr.c \
	  	ft_strcmp.c \
	 	ft_strncmp.c \
	  	ft_atoi.c \
	  	ft_isalpha.c \
	  	ft_isdigit.c \
	  	ft_isalnum.c \
	  	ft_isascii.c \
	  	ft_isprint.c \
	  	ft_toupper.c \
	  	ft_tolower.c \
	  	ft_strequ.c \
	  	ft_strnequ.c \
	  	ft_putchar.c \
	  	ft_putstr.c \
	  	ft_putendl.c \
	  	ft_putnbr.c \
		ft_memset.c \
		ft_bzero.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strmap.c \
		ft_strdel.c \
		ft_strmapi.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strsplit.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strncat.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strjoinfree.c \
		ft_madeby.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		@$(CC) $(CFLAGS) -c $? $(SRC)
		@ar rc $(NAME) $? $(OBJ)
		@ranlib $(NAME)
		@echo "\033[32mBuilt library.\033[0m"

clean:
		@/bin/rm -f $(OBJ)
		@echo "\033[32mCleaned up object files.\033[0m"

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[32mCleaned up compiled files.\033[0m"

re: fclean all

.PHONY: clean fclean re
