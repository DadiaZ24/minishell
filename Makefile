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

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -lreadline
NAME			= minishell

INC				= -I./include
LIBFT			= libs/libft/libft.a

READLINE_PATH    = vendor/readline/
RLFLAG             = -L$(READLINE_PATH)/lib -lreadline

GENERAL			= main.c
PARSING			= #parser.c mini_split.c mini_split_wc.c
UTILS			= #init.c free.c
EXECUTOR		= executor.c pwd.c

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC				= $(GENERAL)\
					$(PARSING)\
					$(UTILS)\
					$(EXECUTOR)\

VPATH 			= src\
					src/parsing\
					src/utils\
					src/executor\
					src/executor/builtins\

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj
				mkdir -p obj/executor
				mkdir -p obj/executor/builtins

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) $(LIBFT) -o $(NAME)

$(LIBFT):
				make -C libft

clean:
				$(RM) $(OBJ) readline.supp

fclean: 		clean
				$(RM) $(NAME) $(OBJ_DIR)

re: 			fclean all

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

.PHONY: 		all clean fclean re
