# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elsie <elsie@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:40:07 by eleotard          #+#    #+#              #
#    Updated: 2023/09/10 18:45:36 by elsie            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

SRCS =	main.cpp \
		RPN.cpp \

OBJS = ${SRCS:%.cpp=%.o}

CC = c++

RM = rm -rf

FLAGS = -Wall -Wextra -Werror -g -std=c++98

%.o: %.cpp
	${CC} ${FLAGS} -o $@ -c $^

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
	
