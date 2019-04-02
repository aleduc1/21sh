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

VPATH = objs:srcs:srcs/lexer:srcs/lexer/dll_lex:srcs/lexer/token:srcs/prompt:srcs/parser
# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3 -fsanitize=address
else
	CFLAGS = -g3 -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)

LFLAGS = -ltermcap

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
			 ampersand.c \
			 brace.c \
			 bracket.c \
			 colon.c \
			 great.c \
			 less.c \
			 par.c \
			 pipe.c \
			 quote.c \
			 sign.c \
			 slash.c \
			 space.c \
			 number.c \
			 word.c \
			 delim.c \
			 cursortools.c \
			 dlist.c \
			 editiontools.c \
			 editline.c \
			 history.c \
			 init.c \
			 keyhook.c \
			 morekeyhook.c \
			 othertools.c \
			 stalkcursor.c \
			 terminit.c \
			 textselection.c \
			 tree_utils.c \
			 parser.c

OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = sh21.h lexer.h parser.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = echo
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs help

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(OBJS_NAMES) $(LIBS)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) "Executable built"

libs :
	@$(MAKE) -C $(LIBDIR)

%.o : %.c $(HEADER)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) ".o created"

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

lldb :
	@lldb ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs and help"

.PHONY : $(PHONY)
