# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 03:02:00 by mabdessm          #+#    #+#              #
#    Updated: 2024/09/27 14:11:42 by mabdessm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
INCLUDES = -I./includes

SRCS = 	printf/ft_printf.c printf/ft_putchar.c printf/ft_putnbr_base.c \
		printf/ft_putnbr_base_p.c printf/ft_putnbr.c printf/ft_putstr.c \
		printf/ft_putunsigned.c printf/ft_strlen.c mandatory/pipex.c \
		mandatory/ft_split.c mandatory/assign.c mandatory/exec.c \
		mandatory/free.c mandatory/utils.c

BONUS_SRCS = printf/ft_printf.c printf/ft_putchar.c printf/ft_putnbr_base.c \
		printf/ft_putnbr_base_p.c printf/ft_putnbr.c printf/ft_putstr.c \
		printf/ft_putunsigned.c printf/ft_strlen.c bonus/pipex.c \
		bonus/ft_split.c bonus/assign.c bonus/exec.c bonus/free.c bonus/utils.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(OBJS)
	@echo "\033[0;31mcompiling ${NAME}...\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "\033[0;32m${NAME} compiled!\033[0m"
	@echo

bonus_compile: $(BONUS_OBJS)
	@echo "\033[0;31mcompiling ${NAME}...\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(BONUS_OBJS) $(INCLUDES)
	@echo "\033[0;32m${NAME} compiled!\033[0m"
	@echo

bonus: fclean bonus_compile

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
	@$(RM) $(NAME)
	@echo "\033[0;32m${NAME} executable deleted!\033[0m"
	@echo

re: fclean all

.PHONY: all re clean fclean bonus