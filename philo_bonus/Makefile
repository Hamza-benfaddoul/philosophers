# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 15:34:29 by hbenfadd          #+#    #+#              #
#    Updated: 2023/04/11 13:18:33y hbenfadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= cc 
HEADER	= -I./inc
CFLAGS	=  -Wall -Wextra -Werror -pthread $(HEADER)
RM		= rm -rf

# colors
NONE	= \033[0m
YALLOW	= \033[1;93m
GREEN	= \033[1;32m

# src files
SRC		= ft_atoi_bonus.c ft_usleep_bonus.c philosopheres_bonus.c get_time_ms_bonus.c \
			utils_bonus.c

SRCS	= $(addprefix ./src/, $(SRC)) main_bonus.c 

# obj files
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

%.o:%.c
	@echo "$(GREEN)Compaling file $<$(NONE)"
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS) $(LIBFT)
	@echo  "$(YALLOW)\n[$@]$(NONE)"
	$(CC) $(CFLAGS) $(OBJS) -o $@ 
	
clean :
	@echo "$(GREEN)Cleaning obj files ...$(NONE)"
	$(RM) $(OBJS)
	
fclean : clean
	@echo "$(GREEN)Clean all ...$(NONE)"
	$(RM) $(NAME) 
	
re: fclean all