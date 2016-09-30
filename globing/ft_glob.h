#include "../command/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define DEBUG

#define GLOB_CASE_SENSITIVE 1

int		glob__match(const char *s, const char *format);
void	ft_glob(const char **paths, char **addr, const char *format, const int flags);
