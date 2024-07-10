# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 13:12:50 by itahri            #+#    #+#              #
#    Updated: 2024/07/05 22:09:52 by itahri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

SRCS = $(addprefix srcs/,  main.c args_parsing.c queue_funcs.c routine.c threads_funcs.c time_funcs.c)

INCLUDES = ./includes -I ./libft/includes/

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3

NAME = philosopher

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c  $< -o $@ -pthread

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
