#include <ft_glob.h>

/*
**	J'ai mis un char** c'est uniqument a titre d'exemple
**	On devra utiliser la table de hash a la place
*/

static t_list		*glob__create_list(const char *path, const char *format)
{
	t_list			*results;
	DIR				*rep;
	struct dirent	*entry;
	char			*name;

	results = NULL;
	if ((rep = opendir(path)))
	{
		while ((entry = readdir(rep)))
		{
			name = (char*)entry->d_name;
			if (glob__match(name, format))
				ft_lstadd(&results, ft_lstnew(name, ft_strlen(name) + 1));
		}
		closedir(rep);
	}
	return (results);
}

static char				*glob__create_string(const char *format, char **paths)
{
	t_list	*lst;
	t_list	*tmp;
	int		len;
	char	*ret;

	ret = NULL;
	lst = NULL;
	len = 0;
	while (*paths)
	{
		if ((tmp = glob__create_list(*paths, format)))
			ft_lstadd(&lst, tmp);
		paths++;
	}
	tmp = lst;
	while (tmp)
	{
		len += tmp->content_size;
		tmp = tmp->next;
	}
	if (len)
	{
		ret = ft_strnew(len);
		while (lst)
		{
			tmp = lst->next;
			ft_strcat(ret, (char*)lst->content);
			free(lst->content);
			free(lst);
			lst = tmp;
		}
	}
	return (ret);
}

void						ft_glob(char **paths, char **addr, char *format)
{
	char					*s_replace;

	if ((s_replace = glob__create_string(format, paths)))
	{
		free(*addr);
		*addr = s_replace;
	}
}