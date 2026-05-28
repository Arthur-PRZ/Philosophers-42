# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artperez <artperez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:23:30 by artperez          #+#    #+#              #
#    Updated: 2025/05/23 11:05:03 by artperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
FC = src/main.c src/utils.c src/threads.c src/init.c src/utils2.c \

FO = $(FC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(FO) $(LIBFT_PATH)
	@echo "Compiling philo"
	@$(CC) $(CFLAGS) $(FO) -o $(NAME) -lpthread

clean:
	@rm -f $(FO)
	@echo "Clean .o"

fclean: clean
	@rm -rf $(NAME)
	@echo "Clean .o and philo"

re: fclean all

.PHONY: all clean fclean re