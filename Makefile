# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlecuyer <>                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/28 11:39:35 by hlecuyer          #+#    #+#              #
#    Updated: 2014/01/28 11:39:35 by hlecuyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	push_swap

INCLUDE_DIR			=	includes

LIBFT				=	ft
LIBFT_DIR			=	libft
LIBFT_NAME			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDE_DIR	=	$(LIBFT_DIR)/includes

COMPILER			=	gcc

SRCS				=	main.c \
						inversion2.c \
						inversion.c \
						quick_sort.c \
						action.c

OBJS				=	$(SRCS:.c=.o)

CFLAGS				=	-g3 -O3 -Wall -Wextra -Werror -c			\
						-I $(LIBFT_INCLUDE_DIR) -I $(INCLUDE_DIR)
LFLAGS				=	-L$(LIBFT_DIR) -l$(LIBFT) -o

all: $(LIBFT_NAME)
	$(MAKE) $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(COMPILER) $^ $(LFLAGS) $(NAME)

%.o: %.c
	$(COMPILER) $(CFLAGS) $<

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all build clean fclean re
