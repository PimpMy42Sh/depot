/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 17:04:29 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/05 18:53:53 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "get_next_line.h"
# include <dirent.h>

# include "../libft/libft.h"

# define GREEN   		"\x1b[32m"
# define CYAN    		"\x1b[36m"
# define RED				"\x1b[31m"
# define RESET   		"\x1b[0m"
# define KU					4283163
# define KD					4348699
# define KR					4414235
# define KL					4479771
# define ESC				27
# define ESP				32
# define DEL 				127
# define TILDE			126
# define TAB 				9
# define RET				10
# define HOME				4741915
# define END				4610843
# define CTRL_D			4
# define CTRL_U			21
# define CTRL_P			16
# define CTRL_R			18
# define CTRL_L			12
# define CTRL_T			20
# define U_CUT			117
# define MAX_SIZE		1

/*
** SCHOOL
** # define ALT_LEFT		17465
** # define ALT_RIGHT		17209
** # define ALT_UP			16697
** # define ALT_DOWN		16953
*/

/*
** HOUSE
*/
# define ALT_LEFT		1146821403
# define ALT_RIGHT	1130044187
# define ALT_UP			1096489755
# define ALT_DOWN		1113266971

# define TERM_ENV		"xterm-256color"
# define CURS_POS		"\x1b[6n"
# define LEFT				"le"
# define RIGHT			"nd"
# define DOWN				"do"
# define UP					"up"
# define DEFAULT		"me"
# define REVERSE		"mr"
# define BEGIN			"cr"
# define DOWN_MAJ		"DO"
# define CLEAR 			"cd"
# define SAVE 			"sc"
# define RESTORE 		"rc"
# define CLEAR_TERM "cl"

pid_t										g_father;

typedef struct								s_norme
{
	int										current;
	int										previous;
	char									*old;
	char									*pwd;
	char									*str;
	char									**copy;
	int										boolean;
	int										i;
	int										u;
}											t_norme;

typedef struct								s_tty
{
	struct termios							term;
	struct termios							backup;
}											t_tty;

typedef struct								s_env
{
	char									**environ;
}											t_env;

typedef struct								s_it
{
	int										i;
	int										len;
	int										saved_i;
	int										first;
	int										buffer;
	int										offset;
	char									*tmp_line;
	char									*line;
	char									*tmp_buffer;
	int										r_video;
	int										ws_col;
	int										nb_current_line;
	int										eof;
}											t_it;

typedef struct								s_hist
{
	char									*cmd;
	struct s_hist							*prev;
	struct s_hist							*next;
}											t_history;

typedef struct								s_hash_tree
{
	int										indice;
	struct s_list							*node;
	struct s_hash_tree						*left;
	struct s_hash_tree						*right;
	struct s_hash_tree						*equal;
}											t_hash_tree;

/*
**	errors
*/
void										command_not_find(char *arg);
void										undefined_variable(char *str);
void										env_error(void);
void										permission_denied(char *str,
											char *path);
void										setenv_error(int boolean);
void										unsetenv_error(void);
void										not_access(void);
void										tcgetattr_error(void);
void										tcsetattr_error(void);
void										terminal_not_find(void);
void										cant_move_home(void);
void										no_such_file(char *path);

/*
**	builtins
*/
int											check_bultins(char **av,
											char **env);
int											ft_setenv(char **av, t_env *env);
void										ft_unsetenv(char **av, t_env *env);
int											ft_cd(char **av, t_env *env);
int											ft_env(char **av, char **environ);
void										remove_flags(char **av,
											t_norme *flags);
void										check_variables(t_norme *flags,
											char **av, char **environ);
void										copy_environ(char **av,
											char **environ, t_norme *flags);
void										ft_exit(char **av, t_env *env);
char										*return_pwd(void);

/*
**	free
*/
void										free_env(char *path,
											char **path_env);
void										free_double_array(char **arr);
void										free_elements(char *one,
											char *two, char *three,
											char *four);
void										free_struct(t_norme *s);
void										free_cmd(char **cmd);

/*
**	parse arguments
*/
void										parse_arguments(char **environ,
											char *line, int boolean);
void										check_tilde_and_dollar(char
											**environ, char **av,
											int boolean);
void										replace_envrion_suite_2(char *ret,
											char *search,
											t_norme *norme, char **av);
char										*parse_search(char *ret);
int											return_av_size(char **av);
void										convert_tab(char *str);

/*
**	parse environ
*/
void										remove_env(char **av, int indice);
int											return_env_indice(char **environ,
											char *env);
char										*return_env(char **environ,
											char *env);
void										move_old_and_pwd(t_env *env,
											char *old, char *pwd);
void										map_environ(char **environ);
char										*return_variable(char *str);
void										replace_item(t_norme *flags,
											char *env, char **av,
											int indice);
void										print_env(char **environ);
void										loop_remove_env(char **av,
											t_env *env);
void										replace_item_environ(char **environ,
											char *env, char *av);
void										append_item_environ(t_env *env,
											char *environ, char *av);
int											return_env_size(char **environ);
void										replace_char(t_it *it, char cmd[2]);
int											check_env(char **environ);
char										*append_path(char *environ,
											char *av);

/*
**	init terminal
*/
int											init_terminal_data(t_tty *tty);
t_tty										*ft_stock_term(t_tty *tty);
void										suspend_terminal(void);
void										resumed_terminal(void);
void										reset_term(void);

/*
**	parser
*/
int											check_line(char *line, t_env *env,
											int boolean);
char										**append_set_path(char *cmd);
void										init_struct(t_norme *norme);
void										parse_line(t_it *it);
void										edit_line(t_it *it);
int											return_offset(void);

/*
**	cursor_moves
*/
void										move_left(t_it *it);
void										move_right(t_it *it);
void										del_char(t_it *it);
void										move_begin(t_it *it);
void										move_end(t_it *it);
void										move_one_word_left(t_it *it);
void										move_one_word_right(t_it *it);
t_it										*init_it_struct(void);
void										del_char_buffer(t_it *it,
											int current);
void										del_current(t_it *it);
void										multi_line_text(t_it *it);
void										move_up_and_down(t_it *it);
void										move_n_char(t_it *it, int direction,
											int n);
void										check_move_first_elem(t_it *it);
void										cursor_on_last_pos(t_it *it,
											int line);
void										move_one_word_left_1(t_it *it,
											int i);
void										move_one_word_left_2(t_it *it,
											int i);

/*
**	copy paste
*/
void										ft_cut_select(t_it *it);
void										cut_line(t_it *it);
void										copy_tmpline(t_it *it);
void										paste_line(t_it *it);
void										put_reverse(t_it *it);

/*
**	History
*/
t_history									*ft_stock_history(t_history
											*history);
void										print_history(t_it *it);
t_history									*create_elem(t_history *history,
											char *line);
t_history									*go_to_end(t_history
											*history);
t_history									*up_history(t_history
											*list, t_it *it);
t_history									*down_history(t_history *list,
											t_it *it);

/*
**	Utilities
*/
int											my_putchar(int c);
void										print_prompt(void);
void										check_shlvl(t_env *env);
void										check_only_space(t_it *it);
t_it										*ft_stock_it(t_it *it);
void										go_to_bottom(t_it *it);
int											ft_abs(int i);
char										**malloc_environ(char **environ,
											char *var);
void										path_manager(t_env *env);

/*
**	Hachage
*/
void										parse_path_directories(char **env);
void										insert_node(t_hash_tree **tree,
											t_list *lst);
char										*search_node(t_hash_tree *tree,
											int indice);
int											ft_hash(char *name);
t_hash_tree									*ft_stock_tree(t_hash_tree *tree);
char										*hash_cmd(char *cmd, char
											**environ);

/*
**	Signals
*/
void										rec_size(t_it *it);
void										check_signal(void);

/*
**	DEBUG
*/
void										debug(char *str, int l);
#endif
