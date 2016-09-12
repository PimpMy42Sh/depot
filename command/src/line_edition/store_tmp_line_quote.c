#include "../../include/minishell.h"

void		convert_it_line(t_it *it, t_list *args, char **back)
{
	int		compteur;
	t_list	*begin;

	begin = args;
	compteur = 0;
	while (args)
	{
		compteur += args->content_size;
		args = args->next;
	}
	compteur++;
	ft_memdel((void**)&it->line);
	it->line = ft_strnew(compteur);
	args = begin;
	while (args)
	{
		it->line = ft_strcat(it->line, args->content);
		args = args->next;
	}
	*back = it->line;
}
