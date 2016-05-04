int		chevron_droite_filname(char *cmd, char **args, char *filename, char **environ);
int		double_chevron_droite_filname(char *path, char **args, char *filename, char **environ);
int		run_pipe(char *path1, char **args1, char *path2, char **args2, char **environ);

#include "minishell.h"

int			main(int argc, char **argv, char **environ)
{
	pid_t	child = -1;
	char	*path1;
	char	*path2;
	char	*args1[3];
	char	*args2[3];

	child = fork();
	path1 = "/bin/ls";
	args1[0] = path1;
	args1[1] = "-la";
	args1[2] = NULL;

	path2 = "/bin/cat";
	args2[0] = path2;
	args2[1] = "-e";
	args2[2] = NULL;
	if (child == 0)
		run_pipe(path1, args1, path2, args2, environ);
	//chevron_droite_filname(path1, args1, "TEST SIMPLE", environ);
	//double_chevron_droite_filname(path1, args1, "TEST DOUBLE", environ);
	wait(NULL);
	return (0);
}