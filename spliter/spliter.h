#ifndef SPLITER_H
# define SPLITER_H
# define CHEVRON_DROIT 1
# define CHEVRON_GAUCHE 2
# define DCHEVRON_DROIT 3
# define DCHEVRON_GAUCHE 4
# define CFG_ALL_REDIRECTION_IN 1
# define CFG_ALL_REDIRECTION_OUT 2
# define PARSING_IS_CMDNAME 1
# define PARSING_IS_ARG 2
# define PARSING_IS_REDIR 3
# include <libft/implemt.h>
# include <fcntl.h>
# include <stdio.h>

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
	int				fd_out;
	int				fd_in;
	t_list			*out;
	t_list			*in;
}					t_redirections;

typedef struct		s_pipeline
{
	char			**args;
}					t_pipeline;

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
	int				fd[2];
	int				split_type;
	t_redirections	redirs;
	t_list			*pipeline;
}					t_command;

/*
**	alloc_redirections.c
**
**	Initialisation, allocation et liberation
*/
//void				initialize_redirections(t_term *t);
void				use_agregator_redirection(t_redirections *r, int fd_in, int fd_out);
t_redirection		*new_redirection(t_redirections *t, int type, char *filename);
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
t_command			get_next_command(char **cmd);
void				exec_command(t_command *cmd, char **env);

#endif
