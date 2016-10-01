#include <ft_glob.h>

/*
**	J'ai mis un char** c'est uniqument a titre d'exemple
**	On devra utiliser la table de hash a la place
*/

static char				*glob__create_string(char *format, int flags, int *i, t_list **results)
{
	t_list	*lst;
	t_list	*tmp;
	int		len;
	char	*ret;

	ret = NULL;
	len = 0;
	glob__open_directory(NULL, (char*)format, flags, results);
	
printf("END\n");
	tmp = *results;
	while (tmp)
	{
		(*i)++;
		len += tmp->content_size;
		tmp = tmp->next;
	}
	if (len)
	{
		lst = *results;
		ret = ft_strnew(len);
		len = 0;
		while (lst)
		{

			tmp = lst->next;
			ft_strcpy(ret + len, (char*)lst->content);
			len += lst->content_size;
			if (tmp)
				*(ret + len - 1) = ' ';
			free(lst->content);
			free(lst);
			//printf("===> %s\n", (char*)ret);
			lst = tmp;
		}
	}
	return (ret);
}

int						ft_glob(char **addr, char *format, int flags, t_list **results)
{
	char					*s_replace;
	int					ret;

	ret = 0;
	if (!ft_strcmp("/", format))
	{
		if (addr)
		{
			free(*addr);
			*addr = ft_strdup("/");
		}
	}	
	else if ((s_replace = glob__create_string(format, flags, &ret, results)))
	{
		if (addr)
		{
			free(*addr);
			*addr = s_replace;
		}
		//printf("%s\n", *addr);
	}
	return (ret);
}