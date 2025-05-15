# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artperez <artperez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:23:30 by artperez          #+#    #+#              #
#    Updated: 2025/05/15 09:27:50 by artperez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
FC = src/main.c src/ft_itoa.atoi.c \

FO = $(FC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(FO) $(LIBFT_PATH)
	@echo "Compiling philo"
	@$(CC) $(CFLAGS) $(FO) -o $(NAME)

clean:
	@rm -f $(FO)
	@make clean -sC libft/
	@echo "Clean .o"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -sC libft/
	@echo "Clean .o and philo"

re: fclean all

.PHONY: all clean fclean re