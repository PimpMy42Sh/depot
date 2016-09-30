#include "../command/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define DEBUG
int		glob__match(const char *s, const char *format);
void	ft_glob(char **paths, char **addr, char *format);
