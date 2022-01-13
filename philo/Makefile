# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 13:45:17 by mlecuyer          #+#    #+#              #
#    Updated: 2021/11/24 19:25:09 by mlecuyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	clang -pthread -Wall -Wextra -Werror -g3 #-fsanitize=thread

INC 	= -I./includes

SRCS	=	main.c \
			atoi.c \
			tools.c \
			actions.c \
			init.c \
			checkers.c \
			destroy.c \

FIL = 		$(addprefix srcs/, $(SRCS))

OBJ = 		$(FIL:.c=.o)

BIN = 		$(addsuffix .o, $(SRCS))

.c.o:
			@${CC} ${INC} -c $< -o ${<:.c=.o}

all:		$(NAME)

${NAME}:	$(OBJ)
				$(CC) $(INC) $(OBJ) -o $(NAME)


clean:
			rm -rf $(OBJ)
			
			
fclean:		clean
				rm -f $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re