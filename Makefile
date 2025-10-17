# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 13:09:46 by yingzhan          #+#    #+#              #
#    Updated: 2025/10/17 13:11:43 by yingzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -pthread
RM = rm -f
INCLUDES = -I./includes/
SRCS = main.c monitor_thread.c philo_thread.c utils1_mutex.c utils2_cleanup.c utils3_others.c init.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re