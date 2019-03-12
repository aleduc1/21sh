# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# ----- #
# Shell #
# ----- #

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SHELL = /bin/zsh
else
	SHELL = /bin/bash
endif

# --------- #
# Directory #
# --------- #

SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
LIBDIR = libs/

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS = -Wall -Wextra
endif
CPPFLAGS = -I $(INCDIR)

LDFLAGS =

# --------------- #
# Differents name #
# --------------- #

NAME = $(LIBDIR)libft.a

SRCS_NAMES = ft_atoi.c ft_bzero.c ft_fill_str.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			 ft_isspace.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lst_element_at.c ft_lstextend.c \
			 ft_lstflip.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_lsttail.c ft_memalloc.c ft_memccpy.c \
			 ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_mergesort.c ft_parser.c \
			 ft_printf.c ft_print_word_table.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
			 ft_putnbr_fd.c ft_putnbrln.c ft_putstr.c ft_putstr_fd.c ft_sort_integer_table.c ft_split_whitespaces.c \
			 ft_strbeginswith.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
			 ft_strendswith.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strjoinfree.c ft_strlcat.c \
			 ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strnchr.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
			 ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strsubfree.c \
			 ft_strtrim.c ft_swap.c ft_tolower.c ft_toupper.c get_next_line.c split_once.c ft_dlstnew.c ft_dlstinserts.c \
			 ft_dlstdel.c ft_dlstprint.c ft_madeby.c ft_debug.c
OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = libft.h ft_printf.h get_next_line.h

SRC = $(addprefix $(SRCDIR), $(SRCS_NAMES))
OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

AR = ar
ARFLAGS = rc
SORT = ranlib
CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = echo
PHONY = all clean fclean re help

# ----- #
# Rules #
# ----- #

all : $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) ""
else
	@$(PRINT) "\n"
endif

$(NAME) : $(OBJ)
	@$(CREATE) $(LIBDIR)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@$(SORT) $(NAME)
	@$(PRINT) "Libft.a built"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) ".o file for lib created"

clean :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file for lib deleted"

fclean : clean
	@$(DEL) $(LIBDIR)
	@$(PRINT) "Libft.a destroyed"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, fclean, re and help"

.PHONY : $(PHONY)
