# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfulop <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/03 01:01:12 by rfulop            #+#    #+#              #
#    Updated: 2017/05/30 20:45:36 by rfulop           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = g++
CFLAGS = -Wall -Wextra -Werror
NAME = morpion

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH =

SRC_FILES = main.cc \
						error.cc \
						run.cc \
						board.cc \
						game.cc 
						#rendering.c \
#						logic.c \

INC_FILES = game.h \

LIB_FILES = -lSDL2 -lSDL2_gfx

OBJ_FILES = $(SRC_FILES:.cc=.o)

OBJ_EXEC = $(addprefix $(OBJ_PATH),$(OBJ_FILES))

LIBFT = $(addprefix $(LIB_PATH),$(LIB_FILES))

all: $(NAME)

$(OBJ_PATH) :
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)%.o : $(SRC_PATH)%.cc
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(NAME) : $(OBJ_PATH) $(OBJ_EXEC)
	@echo "\033[32mLinking \033[1;32m$(LIB_FILES)\033[1;0m\033[32m ...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ_EXEC) $(LIBFT) -o $@ -I $(INC_PATH)
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mBinary \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: clean fclean
