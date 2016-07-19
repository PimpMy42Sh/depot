# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 11:39:04 by mfamilar          #+#    #+#              #
#    Updated: 2016/07/19 15:31:44 by Marco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CXX = gcc

NAME = 21sh

FLAGS = -g

SRC_PATH = ./src/

BUILTINS_PATH = ./src/builtins/

LINE_EDITION_PATH = ./src/line_edition/

BONUS_PATH = ./src/bonus/

ENV_PARSER_PATH = ./src/env_parser/

ARGV_PARSER_PATH = ./src/argv_parser/

ERRORS_PATH = ./src/errors/

INIT_PATH = ./src/init/

OBJ_PATH = ./obj/

INC_PATH = ./include/

LIB_PATH = ./libft

SRC_NAME = 	main.c free.c  utilities.c get_next_line.c debug.c

BUILTINS_NAME = ft_cd.c ft_env.c ft_env_suite.c ft_setenv.c ft_unsetenv.c\
								ft_exit.c

LINE_EDITION_NAME = move_left.c move_right.c copy_paste.c selection_mode.c\
										cursor_moves_one_word_left.c cursor_moves_one_word_right.c\
										write_char.c edit_line.c cursor_moves.c create_history.c\
										cut.c history.c del_char.c insert_char.c del_char_buffer.c\
										check_move_one_word_left.c\

BONUS_NAME = hash_tree.c ft_hash.c hachage.c prompt.c shlvl.c

ENV_PARSER_NAME = parse_environ.c parse_environ_2.c parse_environ_3.c\
									path_manager.c

ARGV_PARSER_NAME = parse_args.c parse_args_2.c parse_args_3.c

ERRORS_NAME = errors.c errors_2.c errors_3.c

INIT_NAME = struct.c init_terminal_data.c suspend_terminal.c signals.c\
						rec_size.c

OBJ_NAME = $(SRC_NAME:.c=.o) $(BUILTINS_NAME:.c=.o) $(LINE_EDITION_NAME:.c=.o)\
						$(BONUS_NAME:.c=.o) $(ENV_PARSER_NAME:.c=.o) $(ERRORS_NAME:.c=.o)\
						$(ARGV_PARSER_NAME:.c=.o) $(INIT_NAME:.c=.o)

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

$(OBJ_PATH)%.o: $(BUILTINS_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(LINE_EDITION_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(BONUS_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(ENV_PARSER_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(ARGV_PARSER_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(ERRORS_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(INIT_PATH)%.c
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
