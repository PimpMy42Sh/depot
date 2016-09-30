#include <ft_glob.h>

/*
**	J'ai mis un char** c'est uniqument a titre d'exemple
**	On devra utiliser la table de hash a la place
*/

static void				glob__list_adding(t_list **lst, const char *s, const int flags)
{
	int		(*compare)();
	t_list	*tmp;
	t_list	*add;
	t_list	*last;

	if (!flags & GLOB_CASE_SENSITIVE)
	{
		compare = NULL;//ft_strcasecmp;
		printf("CASE SENSITIVE NOT IMPLEMENT\n");
	}
	else
		compare = ft_strcmp;
	add = NULL;
	if ((tmp = *lst))
		while (tmp && !add)
		{
			if ((*compare)(s, tmp->content) < 0)
			{
				add = ft_lstnew(s, ft_strlen(s) + 1);
				add->next = tmp;	
				if (last)
					last->next = add;
			}
			last = tmp;
			tmp = tmp->next;
		}
	else
		*lst = ft_lstnew(s, ft_strlen(s) + 1);
}

static t_list		*glob__create_list(const char **paths, const char *format, const int flags)
{
	t_list			*results;
	DIR				*rep;
	struct dirent	*entry;
	char			*name;

	results = NULL;
	while (*paths)
	{
		if ((rep = opendir(*paths)))
		{
			while ((entry = readdir(rep)))
			{
				name = (char*)entry->d_name;
				if (glob__match(name, format))
				{
					printf("-> %s\n", name);
					ft_lstadd(&results, ft_lstnew(name, ft_strlen(name) + 1));
					//glob__list_adding(&results, name, flags);
				}
			}
			closedir(rep);
		}
		paths++;
	}
	(void)flags;
	return (results);
}

static char				*glob__create_string(const char *format, const char **paths, const int flags)
{
	t_list	*lst;
	t_list	*tmp;
	int		len;
	char	*ret;

	ret = NULL;
	len = 0;
	lst = glob__create_list(paths, format, flags);
	tmp = lst;
	while (tmp)
	{
		len += tmp->content_size;
		printf("===> %s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
	if (len)
	{
		ret = ft_strnew(len);
		while (lst)
		{
			tmp = lst->next;
			ft_strcat(ret, (char*)lst->content);
			ft_strcat(ret, " ");
			free(lst->content);
			free(lst);
			lst = tmp;
		}
	}
	return (ret);
}

void						ft_glob(const char **paths, char **addr, const char *format, const int flags)
{
	char					*s_replace;

	if ((s_replace = glob__create_string(format, paths, flags)))
	{
		free(*addr);
		*addr = s_replace;
		printf("%s\n", *addr);
	}
}