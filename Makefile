# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 03:02:00 by mabdessm          #+#    #+#              #
#    Updated: 2024/09/12 00:04:43 by mabdessm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
INCLUDES = -I./includes

SRCS = 	printf/ft_printf.c printf/putunsigned.c printf/ft_putnbr_base_p.c \
		printf/ft_putchar.c printf/putnbr.c printf/putstr.c printf/ft_strlen.c \
		pritnf/ft_putnbr_base.c mandatory/pipex.c mandatory/test.c

BONUS_SRCS = 

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(OBJS)
	@echo "\033[0;31mcompiling ${NAME}...\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "\033[0;32m${NAME} compiled!\033[0m"
	@echo

bonus: $(BONUS_OBJS)
	@echo "\033[0;31mcompiling ${BONUS_NAME}...\033[0m"
	@$(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(INCLUDES)
	@echo "\033[0;32m${BONUS_NAME} compiled!\033[0m"
	@echo

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES)
	
all: $(NAME)

clean:
	@echo "\033[0;31mdeleting objects...\033[0m"
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[0;32mobjects deleted!\033[0m"
	@echo

fclean: clean
	@echo "\033[0;31mdeleting ${NAME} executable...\033[0m"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "\033[0;32m${NAME} executable deleted!\033[0m"
	@echo

re: fclean all

.PHONY: all re clean fclean bonus