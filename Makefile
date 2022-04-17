# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 11:14:54 by acretu            #+#    #+#              #
#    Updated: 2022/04/14 23:28:42 by acretu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -ggdb3 -pthread -fsanitize=thread

SRC			=	main.c \
				main_helpers.c \
				libft_helpers.c \
				philo_helpers.c \
				struct_helpers.c \
				struct_helpers_2.c \
				thread_helpers.c \
				thread_helpers_2.c

OBJ			=	${SRC:.c=.o}

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
