#ifndef COMMAND_H
# define COMMAND_H
# define CHEVRON_DROIT 1
# define CHEVRON_GAUCHE 2
# define DCHEVRON_DROIT 3
# define DCHEVRON_GAUCHE 4
# define OR_OPERATOR 5
# define AND_OPERATOR 6
# define CFG_ALL_REDIRECTION_IN 1
# define CFG_ALL_REDIRECTION_OUT 2
# define CFG_ALL_REDIRECTION_ERR 4
# define HDOC_TMP_FILENAME "/tmp/hdoc"
# define MAX_AGR 10
# include "../libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_norme_command
{
	int					len;
	int					alloc;
	char				*str;
}						t_norme_command;

typedef struct			s_agregateur
{
	int					fd_1;
	int					fd_2;
	int					close;
	char				*filename;
}						t_agregateur;

typedef struct			s_redirection
{
	int					type;
	char				*filename;
	int					fd;
	int					stdfd;
}						t_redirection;

typedef struct			s_redirections
{
	t_list				*agr;
	t_list				*normal;
}						t_redirections;

typedef struct			s_command
{
	t_redirections		redirs;
	t_list				*args;
	char				**argv;
	int					need_redir;
}						t_command;

/*
**	Alloc_redirections.c
*/
t_redirection			*new_redirection(t_redirections *t, int fd, int type,
						char *filename);
void					redirection_add(t_list **alst, t_redirection *new);
void					end_redirections(t_redirections *redirs);

/*
**	Make_redirections.c
*/
void					do_redirections(t_redirections *redirs,
						int in, int out);

/*
**	Identification.c
*/
int						is_a_redirection(char *cmd);
int						is_a_spec_char(int c);

/*
**	Deps.c
*/
char					*ft_strword(char *s);
t_list					*ft_lstnew_noalloc(void *cnt, size_t cnt_size);
int						ft_lstsize(t_list *t);
void					ft_lstadd_end(t_list **addr, t_list *lst);
char					**lst_to_tab(t_list *lst);

/*
**	Get_pipeline.c
*/
t_list					*get_pipeline(char **s, t_env *e);

/*
**	Get_command.c
*/
t_command				*get_command(char **s, t_env *e);

/*
**	Dbg_command.c
*/
void					free_command(t_command *c);
void					realloc_copy(char **s, char **str, int *len);

/*
**	Verification.c
*/
int						verification_pipeline(t_list *pipeline);

/*
**	Identification.c
*/
int						is_a_spec_char(int c);

/*
**	Pipes.c
*/
void					execute_pipes(t_list *cmds, t_env *env);

/*
**	Exec.c
*/
void					stop_cmd(t_list *pipeline);
void					start_prgm(char **env, char **argv);
int						execution__simple_command(t_command *c, t_env *e);
int						execution(t_list *pipeline, t_env *e);

/*
**	Agregateur.c
*/
void					do__agr_close(t_list *lst);
void					do__agr_dup(t_list *lst);

/*
**	Hdoc.c
*/
int						hdoc(char *eof, int fd, char *s, char **env);

/*
**	All_hdoc.c
*/
int						do_all_hdoc(char *cmd, char **env);

/*
**	Hdoc_utils.c
*/
int						nhdoc(int reset);
void					prepare_hdoc(t_redirection *r);
char					*get_filename(int i);
void					hdoc__reset(t_it *it, int prompt);

/*
**	Build.c
*/
void					build_agregateur(t_redirections *r, int fd,
							int type, char **cmd);
int						build_redirection(t_redirections *r, char **cmd);

/*
**	Other
*/
int						check_syntax_quotes(char *s, char **back);
int						check_bultins(t_command *c, t_env *e);
int						alloc_size(int len);
#endif
