#include "../command/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define DEBUG
#define GLOB_LAST 1
#define GLOB_FIRST 2
#define GLOB_CASE_SENSITIVE 4

t_list	*ft_lstnew_noalloc(const void *cnt, size_t cnt_size);
int			ft_strcasecmp(const char *s1, const char *s2);

int		glob__open_directory(char *local, char *pattern, int flags, t_list **results);
int		glob__match(char *local, char *s, char *format, t_list **results);
int		ft_glob(char **addr, char *format, int flags, t_list **results);
