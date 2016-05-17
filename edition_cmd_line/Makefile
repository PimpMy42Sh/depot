# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 11:39:04 by mfamilar          #+#    #+#              #
#    Updated: 2016/05/17 11:06:50 by mfamilar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CXX = gcc

NAME = 21sh

FLAGS = -g 

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/

LIB_PATH = ./libft

SRC_NAME = 	main.c free.c parse_args.c errors.c parse_args_2.c\
			ft_cd.c prompt.c parse_environ.c ft_env.c parse_args_3.c\
			parse_environ_3.c struct.c ft_env_suite.c errors_2.c ft_setenv.c\
			parse_environ_2.c ft_unsetenv.c shlvl.c init_terminal_data.c\
			ft_exit.c utilities.c parser.c edit_line.c suspend_terminal.c\
			cursor_moves.c cursor_moves_2.c cursor_moves_one_word_left.c\
			cursor_moves_one_word_right.c history.c history_2.c del_char.c\
			signals.c errors_3.c copy_paste.c select_text.c rec_size.c

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
