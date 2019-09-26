# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nharra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/15 15:50:31 by nharra            #+#    #+#              #
#    Updated: 2019/09/26 14:00:16 by nharra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

SOURCES =\
	ft_parse.c\
	ft_printf_check.c\
	ft_printf.c\
	len.c\
	print_c.c\
	print_d.c\
	print_p.c\
	print_u.c\
	print_s.c\
	print_params.c\
	num_to_str.c\
	put_percent.c\

SOURCES_DIR = src

SOURCES_UTILS_DIR = utilits

SOURCES_UTILS =\
	ft_atoi.c\
	ft_bzero.c\
	ft_strlen.c\
	ft_strjoin.c

OBJECTS_DIR = obj

vpath %.c = $(SOURCES_DIR) $(SOURCES_UTILS_DIR)

OBJ = $(SOURCES:.c=.o) $(SOURCES_UTILS:.c=.o)

OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(OBJ))

INC_DIR = includes

NAME = libftprintf.a

vpath %.h = $(INC_DIR)

all :$(NAME)

test: all
	gcc $(FLAGS) -I $(INC_DIR) libftprintf.a src/test.c -o test

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: %.c ft_printf.h
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@


$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(OBJECTS): | $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJECTS_DIR)

re: fclean all

.PHONY: all, clean, fclean, re
