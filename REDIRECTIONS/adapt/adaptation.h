#ifndef ADAPTATION_H
# define ADAPTATION_H
# include <dlist.h>
# include <grammar.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct	s_term
{
	int		last_return;
	char	**env;	
}				t_term;

/*
**	==========================================================================
**	======================  Adpatation des redirections ======================
**	==========================================================================
**
**	Outils
*/
int		rewind_cmd(t_dlist **ptr);
char	**get_last_argv(t_dlist *dl);
char	**get_next_argv(t_dlist *dl);
int		open_redirection(t_redirection *r, int flags);

/*
**	Procedures
*/
int		run_pipe(t_term *t, char *path1, char *path2, t_dlist *pipe_op);
int		chevron_droite(t_term *t, char *path, char **args, t_redirection *r);
int		double_chevron_droite(t_term *t, char *path, char **args, t_redirection *r);
int		run_pipe(t_term *t, char *path1, char *path2, t_dlist *pipe_op);
int		double_chevron_droite_filename(t_term *t, char *path, char **args, char *filename);
int		chevron_droite_filename(t_term *t, char *path, char **args, char *filename);


int		parse (t_term *t, const char *cmd);
int		do_redirection(t_term *t, t_redirection *r, t_dlist *states);
#endif