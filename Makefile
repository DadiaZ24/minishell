# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:55:42 by ddias-fe          #+#    #+#              #
#    Updated: 2024/10/24 16:55:42 by ddias-fe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# _______________________________________________________________
#|___________________________[VARIABLES]_________________________|
#|_______________________________________________________________|

NAME = minishell
LIBFT = libs/libft/libft.a
SRC_DIR = ./src
OBJ_DIR = ./obj

#COMPILE/RULE TOOLS
CC = cc
READLINE_PATH    = vendor/readline/
RLFLAG           = -L$(READLINE_PATH)/lib -lreadline
CFLAGS = -Wall -Wextra -Werror -g -I./include
RM = rm -f
RMDIR = rmdir

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/executor/builtins/pwd.c \



OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all: deps $(NAME)

deps:
#	COMPILE LIBFT LIBRARY
	$(MAKE) -C ./libs/libft

#	CREATE OBJECTS FOLDER
	@mkdir -p $(OBJ_DIR)/utils \
		$(OBJ_DIR)/ \
		$(OBJ_DIR)/executor/builtins/ 
	@echo "Created object directories."

$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(MAKE) clean -C ./libs/libft
	$(RM) $(OBJ)

fclean: clean
	@$(RM) $(LIBFT) $(NAME)
	@$(RMDIR) $(OBJ_DIR)/utils \
			$(OBJ_DIR)

gdb:
	gdb -tui ./minishell

re: fclean all
