# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: samkortekaas <samkortekaas@student.codam.nl> +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/26 15:03:14 by samkortekaas  #+#    #+#                  #
#    Updated: 2020/04/28 12:40:12 by samkortekaas  ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_strtoll.c \
              mutex.c \
              utils.c \
              philosophers.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
NAME = philo_one

OBJ := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

debug:
	$(CC) $(CFLAGS) -g $(SRCS) -o $(NAME)

asan: $(OBJ)
	$(CC) $(CFLAGS) -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -o
	$(NAME)

usan: $(OBJ)
	$(CC) $(CFLAGS) -g -fsanitize=undefined -fno-omit-frame-pointer $(SRCS) -o
	$(NAME)

.PHONY: clean fclean re all test

clean:
	-rm -f $(OBJ)

fclean: clean
	-rm -f $(NAME)
	-rm -rf philo_one.dSYM

re: fclean all
