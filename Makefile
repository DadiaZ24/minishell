# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 11:02:10 by ptorrao-          #+#    #+#              #
#    Updated: 2024/10/31 17:21:10 by ptorrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -lreadline
NAME			= minishell

INC				= -I./include
LIBFT			= libft/libft.a

GENERAL			= main.c minishell.c
PARSING			= parser.c mini_split.c mini_split_wc.c
UTILS			= init.c free.c

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC				= $(GENERAL)\
					$(PARSING)\
					$(UTILS)\

VPATH 			= src\
					src/parsing\
					src/utils\
					#src/init\
					src/free\

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ)-o -Llibft -lft $(NAME)

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