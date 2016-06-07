# include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# define PERMISSION_DENIED -1
# define COMMAND_NOT_FOUND -2

int		execute_cmd(char *path, char **args, char **environ);
int		chevron_droite(char *path, char **args, char *filename, char **environ);
int		double_chevron_droite(char *path, char **args, char *filename, char **environ);
int		chevron_gauche(char *path, char **args, char *filename, char **environ);
int		double_chevron_gauche(char *path, char **args, char *filename, char **environ);
void	parse(char *str, char **environ);
