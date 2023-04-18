# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:40:07 by eleotard          #+#    #+#              #
#    Updated: 2023/04/18 19:01:22 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

SRCS =	main.cpp \
		BitcoinExchange.cpp \

OBJS = ${SRCS:%.cpp=%.o}

CC = c++

RM = rm -rf

FLAGS = -Wall -Wextra -Werror -std=c++98

%.o: %.cpp
	${CC} ${FLAGS} -o $@ -c $^

all: ${NAME}

${NAME}:
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
	
