# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/29 19:34:38 by sbelondr          #+#    #+#              #
#    Updated: 2019/07/09 12:38:07 by sbelondr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# --------- #
# Directory #
# --------- #

LIBDIR = libft/
PATHLIBDIR = libft/libs/
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
INCLIBDIR = libft/includes/

VPATH = objs:\
		srcs:\
		srcs/lexer:\
		srcs/lexer/dll_lex:\
		srcs/lexer/token:\
		srcs/prompt:\
		srcs/prompt/edition:\
		srcs/prompt/history:\
		srcs/prompt/multiline:\
		srcs/prompt/others:\
		srcs/prompt/selection:\
		srcs/parser:\
		srcs/parser/pre_parser:\
		srcs/parser/pre_parser/simple_command:\
		srcs/parser/pre_parser/remove_space:\
		srcs/parser/pre_parser/redirect:\
		srcs/parser/pre_parser/redirect/grammar:\
		srcs/parser/ast:\
		srcs/parser/command:\
		srcs/commands:\
		srcs/cleaning:\
		srcs/interpreter:\
		srcs/builtins:\
		srcs/env:\
		srcs/redirection

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)
LFLAGS = -lncurses

# --------------- #
# Different names #
# --------------- #

NAME = 21sh

SRCS_NAMES = main.c \
			 lexer.c \
			 types.c \
			 dll_new.c \
			 dll_ins.c \
			 dll_iter.c \
			 dll_del.c \
			 token.c \
			 simple_command.c \
			 delim.c \
			 type_check.c \
			 attach.c \
			 cursortools.c \
			 dlist.c \
			 dlist_plus.c \
			 editiontools.c \
			 editline.c \
			 history.c \
			 prompt.c \
			 keyhook.c \
			 morekeyhook.c \
			 del_keyhook.c \
			 othertools.c \
			 stalkcursor.c \
			 terminit.c \
			 multiline.c \
			 heredoc.c \
			 text_selection.c \
			 copy_paste.c \
			 undo_selection.c \
			 delete_selection.c \
			 redirect.c \
			 clean_lex.c \
			 handle_great.c \
			 handle_great_and.c \
			 handle_and_great.c \
			 handle_append.c \
			 handle_less.c \
			 handle_less_and.c \
			 handle_and_less.c \
			 handle_heredoc.c \
			 handle_great_hyph.c \
			 handle_less_hyph.c \
			 rules_great.c \
			 is_a_redirect.c \
			 ast_parser.c \
			 ast_parser_tools.c \
			 tree_utils.c \
			 cmd_parser.c \
			 builtin_env.c\
			 commands.c\
			 commands_pipe.c\
			 execute_command.c\
			 list_env.c\
			 free_env.c\
			 list_redirection.c\
			 manage_env.c\
			 manage_set.c\
			 manage_variable.c\
			 manage_file.c\
			 manage_quote.c\
			 other_tools.c\
			 parser_var.c\
			 apply_parser_var.c\
			 tools_env.c \
			 add_quote.c\
			 remove_space_token.c \
			 interpreter.c \
			 clean_redir.c \
			 adding_token.c \
			 handle_stuff.c \
			 reading_tools.c \
			 if_checks.c \
			 bt_exit.c \
			 bt_echo.c\
		 	 builtin_cd.c\
			 builtin_cd_verif.c\
			 list_redirect.c\
			 redirection.c\
			 redirection_bis.c\
			 signal.c\
			 path.c\
			 parameter_expansion.c\
			 formats_parameter.c\
			 formats_parameter_bis.c\
			 delete_redirection.c\
			 check_last.c\
			 action_pipe.c\
			 list_process.c\
			 tools_setenv.c\
			 test_quote.c\
			 gest_error_exec.c


OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = sh21.h lexer.h parser.h env.h builtins.h commands.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"

# PROGRESS BAR | Original author Cpirlot
T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C  '*' 100 / $T`%]"

# ----- #
# Rules #
# ----- #

all : $(LIBS) $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(LIBS) $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) $(REMOVE)"Executable built\n"

$(LIBS) :
	@$(MAKE) -j3 -C $(LIBDIR)

%.o : %.c $(HEADER)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed\n"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

lldb :
	@lldb ./$(NAME)

norm :
	@norminette ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs, lldb, norm and help\n"

.PHONY : $(PHONY)
