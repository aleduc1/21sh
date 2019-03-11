.PHONY: all, $(NAME), clean, fclean, re

NAME = 21sh

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -g -Wall -Werror -Wextra
FRAM = 

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./include/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ft_ls.h
SRC_NAME = cursortools.c dlist.c editiontools.c editline.c history.c keyhook.c \
		   morekeyhook.c othertools.c stalkcursor.c terminit.c textselection.c \
		   main.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@echo
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) -L $(LFT_PATH) -lft -lncurses $^ -o $@
		@echo "\033[32m21sh ready.\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<
		@echo -n =

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "\033[32mDeleting [./obj] directory.\033[0m"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "\x1b[31mSUCESSFULLY CLEANED 21sh\x1b[31m"

re: fclean all 