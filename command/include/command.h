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
# define MAX_AGR 9
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

/*
**	Redirection data structure
**
**	type:		type de redirection
**	filename:	nom du fichier
**	fd:			file descriptor
*/

typedef struct		s_redirection
{
	int				type;
	char			*filename;
	int				fd;
}					t_redirection;

/*
**	Redirections datas 	(MERCI MERLIN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
**
**	fd_out/in:		bit a 1 <=>	redirection dans le fd du n_bit (argregateur)
**	out/in:			liste de redirection a faire
*/

typedef struct		s_redirections
{
	int				fd_agr1[MAX_AGR];
	int				fd_agr2[MAX_AGR];
	int				close_fd[MAX_AGR];

	t_list			*out;
	t_list			*in;
	t_list			*err;
}					t_redirections;

/*
**	Commande
**
**	fd: 		pipe
**	split_type:	spliter par ;, || ou bien &&
**	redirs:		redirections des entrees/sorties d'une suite de commande
**	pipeline;	liste de commande (dont les contents sont les args)
*/

typedef struct		s_command
{
	t_redirections	redirs;
	t_list			*args;
	char			**argv;
	int				need_redir;
}					t_command;

/*
**	alloc_redirections.c
**
**	Initialisation, allocation et liberation
*/
void				prepare_hdoc(t_redirections *t, t_redirection *r);
t_redirection		*new_redirection_err(t_redirections *t, int type,
					char *filename);
t_redirection		*new_redirection(t_redirections *t, int type,
					char *filename);
void				end_redirection(t_redirection *r);
void				end_redirections(t_redirections *redirs);
int					do_all_hdoc(char *cmd);


/*
**	make_redirections.c
**
**	Parsing et execution
*/

int					build_redirection(t_redirections *r, char **cmd);
int					ft_pipes(t_list *cmds, int child, t_env *env);

/*
**	split_cmd.c
**
**	Parser de commande
*/

int					is_a_redirection(char *cmd);
char				**lst_to_tab(t_list *lst);
t_command			*get_command(char **s, t_env *e);
void					exec_command(t_command *cmd, t_env *env);

/*
**	deps.c
**
**	Dependances
*/

char				*ft_strword(char *s);
t_list				*ft_lstnew_noalloc(void *cnt, size_t cnt_size);
int					ft_lstsize(t_list *t);
void				delete_tab(char **t);

/*
**	eval.c
*/
void			print_command(t_command *c);
void			ft_lstadd_end(t_list **addr, t_list *lst);
void		free_command(t_command *c);
t_list			*get_pipeline(char **s, t_env *e);
void				execution(t_list *pipeline, t_env *e);
int					check_bultins_exit(char **av, t_env *env);
void			do_redirections(int cfg, t_redirections *redirs, int in, int out);
int					verification_line(char *s);
int					verification_pipeline(t_list *pipeline);
int					nhdoc(int reset);

#endif
