#ifndef PARSE_H
# define PARSE_H
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define PERMISSION_DENIED -1
# define COMMAND_NOT_FOUND -2
# define DOUBLE_CHEVRON_DROITE 1
# define SIMPLE_CHEVRON_DROITE 2
# define SIMPLE_CHEVRON_GAUCHE 3
# define DOUBLE_CHEVRON_GAUCHE 4
# define WTF_PIPE -1

/*
**	Parse outils
*/

t_list	*ft_lstnew_noalloc(void *cnt, size_t cnt_size);
void	add_cmd(t_list **ptr, t_list *new);
char	**lst_to_args(t_list *lst);
char	**lst_to_pipe_args(t_list **lst);
t_list	*get_last_cmd(t_list *tmp);
char	*get_next_word(char **str);
t_list	*get_next_cmd(int *type, char **str);

/*
**	Execution
*/

int		test_command(char *path);
int		execute_cmd(char *path, char **args, char **environ);

/*
**	Redirections
*/

int		chevron_droite(t_list *lst, char *filename, char **environ);
int		double_chevron_droite(t_list *lst, char *filename, char **environ);
int		chevron_gauche(t_list *lst, char *filename, char **environ);
int		double_chevron_gauche(t_list *lst, char *filename, char **environ);
int		ft_pipes (t_list *cmds, char **env);

/*
**	Parsing
*/

void	parse(char *str, char **environ);

#endif
