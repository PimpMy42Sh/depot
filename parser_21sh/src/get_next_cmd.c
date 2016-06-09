#include <parse.h>

/*
**	Attribue un type de redirection
*/

static int	attribute_type(char *str)
{
	int	type;

	if (*str == '>')
		type = *(str + 1) == '>' ?
		DOUBLE_CHEVRON_DROITE : SIMPLE_CHEVRON_DROITE;
	else if (*str == '<')
		type = *(str + 1) == '<' ?
		DOUBLE_CHEVRON_GAUCHE : SIMPLE_CHEVRON_GAUCHE;
	else
		type = -1;
	return (type);
}

static char	*parse_token(char **str, char **cpy, char *alloc_word, t_list **lst)
{
	if (**str == ' ')
	{
		while (**str == ' ')
			(*str)++;
		add_cmd(lst, ft_lstnew_noalloc(alloc_word, ft_strlen(alloc_word)));
		alloc_word = ft_strnew(1024);
		*cpy = alloc_word;
		(*str)--;
	}
	else if (**str == '|')
	{
		add_cmd(lst, ft_lstnew_noalloc(NULL, -1));
	}
	else if (**str != ';')
	{
		**cpy = **str;
		(*cpy)++;
	}
	return (alloc_word);
}

/*
**	Renvoie une liste de string (une commande et son type d'execution)
**	type: addr du type (-1 par def)
**	str: addr de la ligne de commande
*/

t_list		*get_next_cmd(int *type, char **str)
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
			*str +=
			(*type == DOUBLE_CHEVRON_DROITE || *type == DOUBLE_CHEVRON_GAUCHE);
		else
		{
			alloc_word = parse_token(str, &cpy, alloc_word, &lst);
		}
		(*str)++;
	}
	if (alloc_word != cpy)
	{
		add_cmd(&lst, ft_lstnew_noalloc(alloc_word, ft_strlen(alloc_word)));
		alloc_word = ft_strnew(1024);
		cpy = alloc_word;
	}
	return (lst);
}

/*
**	Renvoie le prochain mot
**	(utile pour les nom de fichier pour les redirections)
**	str: addresse de la ligne
*/

char		*get_next_word(char **str)
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
