# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 15:01:19 by houmanso          #+#    #+#              #
#    Updated: 2024/02/02 15:01:56 by houmanso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RPN
SRC		= $(wildcard *.cpp)
HDR		= $(wildcard *.hpp)
OBJ		= $(SRC:.cpp=.o)
CPPFLAGS= -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME)	:$(OBJ)
	c++ $(CPPFLAGS) $(OBJ) -o $@

%.o : %.cpp $(HDR)
	c++ $(CPPFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: clean
