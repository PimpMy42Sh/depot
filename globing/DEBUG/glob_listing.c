#include <ft_glob.h>

char						*stock_path(char *path)
{
	static char				*keep = NULL;

	if (path)
		keep = path;
	return (keep);
}

static void				glob__list_adding(t_list **lst, char *s, int flags)
{
	int		(*compare)();
	t_list	*tmp;
	t_list	*add;
	t_list	*last;
	int		ret;

	/*if (!(flags & GLOB_CASE_SENSITIVE))
	{
		compare = NULL;//ft_strcasecmp;
		printf("CASE SENSITIVE NOT IMPLEMENT\n");
	}
	else*/
	compare = ft_strcasecmp;
	add = NULL;
	last = NULL;
//	printf("adding\n");
	if ((tmp = *lst))
		while (tmp && !add)
		{
	//		printf("%s\n", (char*)tmp->content);
			ret = (*compare)(s, tmp->content);
			if (ret < 0)
			{
				add = ft_lstnew_noalloc(s, ft_strlen(s) + 1);
				add->next = tmp;	
				if (last)
					last->next = add;
				else
					(*lst) = add;
			}
			else if (ret == 0)
				return ;
			last = tmp;
			tmp = tmp->next;
		}
	else
		*lst = ft_lstnew_noalloc(s, ft_strlen(s) + 1);
}

static char			*glob__get_path(char *local, char *name, int set)
{
	int				i;
	char			*path;
	char			*fullpath;
	int				j;

	i = 0;
	j = 0;
	while (name[i] && name[i] != '*' && name[i] != '[' && name[i] != '?')
	{
		if (name[i] == '/')
			j = i;
		i++;
	}
	if (!local)
	{
		if (!i)
		{
			name = ".";
			j = 1;
		}
		fullpath = ft_strnew(j + 1);
		ft_strncpy(fullpath, name, j);
		ft_strcat(fullpath, "/");
	}
	else
	{
		path = ft_strnew(j + 1);
		ft_strncpy(path, name, j);
		//if (j)
			ft_strcat(path, "/");
		fullpath = ft_strjoin(local, path);
		free(path);
	}
	return (fullpath);
}

static void			glob__correct_pattern(char **name)
{
	char			*tmp;
	int				i;

	i = 0;
	tmp = *name;
	while (	tmp[i] && tmp[i] != '*' &&
			tmp[i] != '[' && tmp[i] != '?')
	{
		if (tmp[i] == '/')
			*name = &tmp[i + 1];
		i++;
	}
	//printf("============== %s\n", *name);
}

static void			glob__correct_path(char **name)
{
	char			*tmp;

	if (!ft_strncmp(*name, "./", 2))
	{
		tmp = ft_strdup((*name) + 2);
		free(*name);
		*name = tmp;
	}
	else if ((*name)[ft_strlen(*name)] == '/')
	{
		tmp = ft_strdup((*name) + 1);
		free(*name);
		*name = tmp;
	}	
}

int				glob__open_directory(char *local, char *pattern, int flags, t_list **results)
{
	DIR				*rep;
	struct dirent	*entry;
	char			*name;
	char			*path;
	char			*tmp;
	int				ret;

	ret = 0;
	if (!ft_strncmp("./", pattern, 2))
	{
		pattern += 2;
		path = ft_strdup("./");
	}
	else
		path = glob__get_path(local, pattern, flags & 2);
	//printf("%s, %s\n", local, pattern);
	glob__correct_pattern(&pattern);
	if ((rep = opendir(path)))
	{
		while ((entry = readdir(rep)))
		{
			name = ft_strjoin(path, entry->d_name);
			glob__correct_path(&name);
			printf("<%s>%s\n", path, name);
			if ((*entry->d_name != '.') &&
				glob__match(name, entry->d_name, pattern, results))
			{
				ret = 1;
				ft_lstadd(results, ft_lstnew(name, ft_strlen(name) + 1));
				//glob__list_adding(results, name, flags);
			}
			else
				free(name);
		}
		closedir(rep);
	}
	free(path);
	return (ret);
}
