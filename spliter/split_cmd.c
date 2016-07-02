#include <spliter.h>

int					IS_A_REDIRECTION(char *cmd) 
{
	return ((ft_isdigit(*cmd) && (*(cmd + 1) == '<' || *(cmd + 1) == '>')) ||
		(*cmd == '<' || *cmd == '>'));
}

char				**lst_to_tab(t_list *lst)
{
	char	**args;
	t_list	*next;
	int		n;

	n = ft_lstsize(lst);
	args = (char**)malloc(sizeof(char*) * (n + 1));
	bzero(args, sizeof(char**) * (n + 1));
	while (lst)
	{
		next = lst->next;
	//	if (*(char*)lst->content)
			args[--n] = (char*)lst->content;
	//	else
	//		n--;
		free(lst);
		lst = next;
	}
	return (args);
}

void				my_pipeline(t_list **ptr, t_list **cmd)
{
	char	**tab;
	t_list	*new;
	t_list	*add;

	add = *ptr;
//	printf("adding pipeline\n");
	tab = lst_to_tab(*cmd);
	new = ft_lstnew_noalloc(tab, sizeof(tab));
	if ((add = *ptr))
	{
		while (add->next)
			add = add->next;
		add->next = new;
	}
	else
		*ptr = new;
/*	while (*tab)
	{
		printf("===> |%s|\n", *tab);
		tab++;
	}
*/
	*cmd = NULL;
}

t_command			get_next_command(char **cmd)
{
	char		*str;
	char		*cpy;
	t_list		*tmp;
	t_command	com;

	tmp = NULL;
	memset(&com, 0, sizeof(t_command));
	cpy = ft_strnew(1024);
	str = (char*)cpy;
	while (**cmd && !IS_A_REDIRECTION(*cmd) && **cmd != ';')
	{
		if (**cmd == '|')
		{
			my_pipeline(&com.pipeline, &tmp);
			(*cmd)++;
		}
		else if (**cmd != ' ')
		{
//			printf("cpy %c (%s)\n", **cmd, cpy);
			*(str++) = *((*cmd)++);
		}
		else
		{
//			printf("adding arg: %s\n", cpy);
			while (**cmd == ' ')
				(*cmd)++;
			if (*(str - 1))
				ft_lstadd(&tmp, ft_lstnew_noalloc(cpy, ft_strlen(cpy)));
			cpy = ft_strnew(1024);
			str = (char*)cpy;
		}
	}
	if (tmp)
			my_pipeline(&com.pipeline, &tmp);
	if (IS_A_REDIRECTION(*cmd))
	{
//		printf("Redirection\n");
		memset(&com.redirs, 0, sizeof(t_redirections));
		build_redirection(&com.redirs, cmd);
	}
	if (cpy == str)
		free(cpy);
	return (com);
}
