# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 11:39:04 by mfamilar          #+#    #+#              #
#    Updated: 2016/09/21 19:24:00 by Marco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CXX = gcc

NAME = 21sh

FLAGS = -Wall -Wextra -Werror -g

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/

LIB_PATH = ./libft

OBJ_NAME = $(addsuffix .o, $(basename $(SRC_NAME)))

SRC_NAME = main.c free.c utilities.c get_next_line.c buitlins/ft_cd.c\
buitlins/ft_env.c buitlins/ft_env_suite.c buitlins/ft_setenv.c\
buitlins/ft_unsetenv.c buitlins/ft_exit.c line_edition/move_left.c\
line_edition/move_right.c line_edition/copy_paste.c\
line_edition/selection_mode.c init/signals.c init/rec_size.c\
line_edition/cursor_moves_one_word_right.c line_edition/write_char.c\
line_edition/edit_line.c line_edition/cursor_moves.c\
line_edition/create_history.c line_edition/cut.c history.c\
line_edition/del_char.c line_edition/insert_char.c\
line_edition/del_char_buffer.c bonus/ft_hash.c\
line_edition/check_move_one_word_left.c bonus/hash_tree.c\
bonus/hachage.c bonus/prompt.c env_parser/parse_environ.c\
env_parser/parse_environ_2.c command/all_hdoc.c init/stock.c\
env_parser/path_manager.c argv_parser/parse_args.c bonus/shlvl.c\
argv_parser/parse_args_2.c argv_parser/parse_args_3.c errors/errors.c\
errors/errors_2.c init/struct.c line_edition/new_line.c\
init/init_terminal_data.c init/suspend_terminal.c\
line_edition/cursor_moves_one_word_left.c\
command/alloc_redirection.c command/deps.c command/exec.c\
command/make_redirection.c command/identification.c\
command/get_command.c command/verification.c command/hdoc.c\
command/hdoc_utils.c command/agregateur.c command/build.c\
command/pipes.c command/get_pipeline.c command/dbg_command.c\
buitlins/checking.c buitlins/ft_echo.c line_edition/check_synthax_and_close.c\
line_edition/not_close.c line_edition/store_tmp_line_quote.c\

LIB_NAME = -lft

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(notdir $(OBJ_NAME)))
INC = $(addprefix -I, $(INC_PATH))
INC += $(addprefix -I, $(LIB_PATH))
LIB = $(addprefix -L, $(LIB_PATH))

VPATH = $(shell find $(SRC_PATH) -type d)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)
	$(CXX) $(FLAGS) $(OBJ) -o $(NAME) $(LIB) $(LIB_NAME) -ltermcap

$(OBJ_PATH)%.o: %.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CXX) $(FLAGS) $(INC) -c $< -o $@

clean:
	make -C $(LIB_PATH) clean
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf ./libft/libft.a
	@rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)
