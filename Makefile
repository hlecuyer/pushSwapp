# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: johnduro <>                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/28 11:39:35 by johnduro          #+#    #+#              #
#    Updated: 2014/01/28 11:39:35 by johnduro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swapp

SRC_S = main.c

OBJ_S = $(SRC_S:.c=.o)


FLAGS = -g3 -Wall -Wextra -Werror

all: build $(NAME) finish

build:
	@make -C libft

$(NAME): $(OBJ_S)
	@gcc $(OBJ_S) -L libft -lft -o $(NAME)


%.o: %.c
	@gcc $(FLAGS) -c -I libft/includes -I includes $<

clean:
	@rm -f $(OBJ_S)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re
