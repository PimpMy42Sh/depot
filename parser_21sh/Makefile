# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 11:39:04 by mfamilar          #+#    #+#              #
#    Updated: 2016/06/07 10:10:54 by mfamilar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CXX = gcc

NAME = 21sh

FLAGS =

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/

LIB_PATH = ./libft

SRC_NAME = 	parse.c chevron_droite.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = -lft

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))
INC += $(addprefix -I, $(LIB_PATH))
LIB = $(addprefix -L, $(LIB_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	MAKE -C $(LIB_PATH)
	$(CXX) $(FLAGS) -ltermcap $(LIB) $(LIB_NAME) $(LIBX_NAME) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

clean:
	MAKE -C $(LIB_PATH) clean
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	rm -rf ./libft/libft.a
	rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)
