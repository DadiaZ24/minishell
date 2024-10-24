# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 14:59:38 by ddias-fe          #+#    #+#              #
#    Updated: 2024/04/09 14:59:38 by ddias-fe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = libft.a

LIB_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c\
		   ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c\
	  	   ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
	  	   ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		   ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c \
		   ft_atol.c
		
LIB_GNL =	ft_strclen.c\
			ft_strndup.c\
			get_next_line.c\

LIB_PRTF =	printf/src/ft_printf_utils.c\
			printf/src/ft_printf_utils2.c\
			printf/src/ft_printf.c\

LIB_OBJS =  $(LIB_SRCS:.c=.o)

GNL_OBJS = 	$(LIB_GNL:.c=.o)

PRTF_OBJS =	$(LIB_PRTF:.c=.o)

all: $(NAME)

$(NAME): $(LIB_OBJS) $(GNL_OBJS) $(PRTF_OBJS)
	@ar rc $(NAME) $(LIB_OBJS) $(GNL_OBJS) $(PRTF_OBJS)
	@echo "Library $(NAME) created."

clean:
	@$(RM) $(LIB_OBJS) $(GNL_OBJS) $(PRTF_OBJS)
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@echo "Library $(NAME) and object files cleaned."
	
re: clean all