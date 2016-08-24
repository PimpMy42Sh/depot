#ifndef SPLITER_H
# define SPLITER_H
# define CHEVRON_DROIT 1
# define CHEVRON_GAUCHE 2
# define DCHEVRON_DROIT 3
# define DCHEVRON_GAUCHE 4
# define CFG_ALL_REDIRECTION_IN 1
# define CFG_ALL_REDIRECTION_OUT 2
# define CFG_ALL_REDIRECTION_ERR 4
# define HDOC_TMP_FILENAME "/tmp/hdoc"
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
	int				fd_agr1;
	int				fd_agr2;
	int				close_fd;
	t_list			*out;
	t_list			*in;
	t_list			*err;
	// int				hdoc;
}					t_redirections;

// typedef struct		s_pipeline
// {
// 	char			**args;
// }					t_pipeline;

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
	// int				mask;
	// int				split_type;
	t_redirections	redirs;
	t_list			*pipeline;
	int				need_redir;
}					t_command;

typedef struct		s_norme_com
{
	char			*str;
	char			*cpy;
	char			**cmd;
}					t_norme_com;

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

/*
**	make_redirections.c
**
**	Parsing et execution
*/
int					build_redirection(t_redirections *r, char **cmd);
void				do_redirections(int cfg, t_redirections *redirs);

/*
**	split_cmd.c
**
**	Parser de commande
*/
int					is_a_redirection(char *cmd);
char				**lst_to_tab(t_list *lst);
t_command			get_next_command(char **cmd);
void				exec_command(t_command *cmd, t_env *env);

/*
**	deps.c
**
**	Dependances
*/
void				init_norme_com(t_norme_com *n, char **cmd);
char				*ft_strword(char *s);
t_list				*ft_lstnew_noalloc(void *cnt, size_t cnt_size);
int					ft_lstsize(t_list *t);
void				delete_tab(char **t);

#endif
