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
              semaphore.c \
              utils.c \
              utils_2.c \
              philosophers.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = philo_three

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

debug: $(SRCS)
	$(CC) $(CFLAGS) -g $(SRCS) -o $(NAME)

.PHONY: clean fclean re all test

clean:
	-rm -f $(NAME)

fclean: clean
	-rm -f $(NAME)
	-rm -rf philo_three.dSYM

re: fclean all
