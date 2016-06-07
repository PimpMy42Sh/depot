
/*
**	A AJOUTER DANS LE HEADER
*/
# include <libft/libft.h>
# include <stdio.h>

# define DOUBLE_CHEVRON_DROITE 1
# define SIMPLE_CHEVRON_DROITE 2
# define SIMPLE_CHEVRON_GAUCHE 3
# define DOUBLE_CHEVRON_GAUCHE 4
# define WTF_PIPE 0

/*
**	Creer un nouveau maillon sans allouer son contenu
*/
t_list	*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*new;

	if ((new = (t_list*)malloc(sizeof(t_list))))
	{
		new->content = cnt;
		new->content_size = cnt_size;
		new->next = NULL;
	}
	else
		new = NULL;
	return (new);
}

/*
**	Equivalent a ft_lstadd
*/
void	add_cmd(t_list **ptr, t_list *new)
{
	t_list	*lst;

	if ((lst = *ptr))
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
		*ptr = new;
}

/*
**	Attribue un type de redirection
*/
int			attribute_type(char *str)
{
	int	type;

	if (*str == '>')
		type = *(str + 1) == '>' ? DOUBLE_CHEVRON_DROITE : SIMPLE_CHEVRON_DROITE;
	else if (*str == '<')
		type = *(str + 1) == '<' ? DOUBLE_CHEVRON_GAUCHE : SIMPLE_CHEVRON_GAUCHE;
	else if (*str == '|')
		type = WTF_PIPE;
	else
		type = -1;
	return (type);
}

/*
**	Renvoie une liste de string (une commande et son type d'execution)
**
**	type: addr du type (-1 par def)
**	str: addr de la ligne de commande
*/
t_list 	*get_next_cmd(int *type, char **str)
{
	char	*alloc_word;
	char	*cpy;
	t_list	*lst;

	lst = NULL;
	alloc_word = ft_strnew(1024);
	cpy = alloc_word;
	while (**str && **str != ';' && *type == -1)
	{
		if ((*type = attribute_type(*str)) != -1)
			*str += (*type == DOUBLE_CHEVRON_DROITE || *type == DOUBLE_CHEVRON_GAUCHE);
		else if (**str == ' ')
		{
			while (**str == ' ')
				(*str)++;
			add_cmd(&lst, ft_lstnew_noalloc(alloc_word, ft_strlen(cpy)));
			alloc_word = ft_strnew(1024);
			cpy = alloc_word;
			(*str)--;
		}
		else
		{
			*cpy = **str;
			cpy++;
		}
		(*str)++;
	}
	if (alloc_word != cpy)
	{
		add_cmd(&lst, ft_lstnew_noalloc(alloc_word, ft_strlen(cpy)));
		alloc_word = ft_strnew(1024);
		cpy = alloc_word;
	}
	return (lst);
}

/*
**	Creer les arguments a envoyer (nom de cmd compris)
**
**	lst: liste de commandes
*/
char	**lst_to_args(t_list *lst)
{
	char	**args;
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	if ((args = (char**)malloc(sizeof(char*) * (size + 1))))
	{
		size = 0;
		while (lst)
		{
			args[size++] = (char*)lst->content;
			lst = lst->next;
		}
		args[size] = (char*)0;
	}
	else
		args = NULL;
	return (args);
}

/*
**	Renvoie le prochain mot (utile pour les nom de fichier pour les redirections)
**
**	str: addresse de la ligne
*/
char	*get_next_word(char **str)
{
	char	*word;
	char	*cpy;

	if ((word = (char*)malloc(sizeof(char) * 1024)))
	{
		cpy = word;
		while (**str == ' ')
			(*str)++;
		while (**str && **str != ' ' && **str != ';')
		{
			*cpy = **str;
			*(cpy + 1) = 0;
			cpy++;
			(*str)++;
		}
	}
	else
		word = NULL;
	return (word);
}

/*
**	Parse: Execute une ligne de commande
**
**	str: ligne de commande
**	environ: environemnt
*/
void	parse(char *str, char **environ)
{
	t_list	*lst;
	t_list	*next;
	int		type;
	char	*filename;
	char	**args;

	lst = NULL;
	type = -1;
	while (*str)
	{
		if ((lst = get_next_cmd(&type, &str)))
		{
			if (type != 0)
			{
				args = lst_to_args(lst);
				if (type == -1)
					execute_cmd(args[0], args, environ);
				else
				{
					filename = get_next_word(&str);
					if (type == SIMPLE_CHEVRON_DROITE)
						chevron_droite(args[0], args, filename, environ);
					else if (type == DOUBLE_CHEVRON_DROITE)
						double_chevron_droite(args[0], args, filename, environ);
					else if (type == SIMPLE_CHEVRON_GAUCHE)
						;
					else if (type == DOUBLE_CHEVRON_GAUCHE)
						;
					free(filename);
				}
				free(args);
			}
			else
			{
				//ft_pipes(*lst) by ayoub
			}
		}
		while (lst)
		{
			next = lst->next;
//			printf("<%s>\n", (char*)lst->content);
			free(lst->content);
			free(lst);
			lst = next;
		}
		type = -1;
	}
}
