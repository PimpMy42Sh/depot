#include <parse.h>

/*
**	Libere la liste de commande
*/

static void		delete_command(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
}

/*
**	Execute une commande
*/

static void		execute_command(t_list *lst, char **str, char **environ,
								int type)
{
	char	**args;
	char	*filename;

	if (type != -1)
	{
		args = lst_to_args(lst);
		filename = get_next_word(str);
		if (type == SIMPLE_CHEVRON_DROITE)
			chevron_droite(lst, filename, environ);
		else if (type == DOUBLE_CHEVRON_DROITE)
			double_chevron_droite(lst, filename, environ);
		else if (type == SIMPLE_CHEVRON_GAUCHE)
			chevron_gauche(lst, filename, environ);
		else if (type == DOUBLE_CHEVRON_GAUCHE)
			double_chevron_gauche(lst, filename, environ);
		free(filename);
		free(args);
	}
	else
		ft_pipes(lst, environ);
}

/*
**	Parse: Execute une ligne de commande
**	str: ligne de commande
**	environ: environemnt
*/

void			parse(char *str, char **environ)
{
	t_list	*lst;
	int		type;

	lst = NULL;
	type = -1;
	while (*str)
	{
		if ((lst = get_next_cmd(&type, &str)))
		{
			execute_command(lst, &str, environ, type);
			delete_command(lst);
		}
		else
			str++;
		type = -1;
	}
}
