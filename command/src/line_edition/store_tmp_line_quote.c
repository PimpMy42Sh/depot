#include "../../include/minishell.h"

 static void	free_structure(t_list *args)
{
	t_list *tmp;

	while (args)
	{
		tmp = args->next;
		ft_memdel((void**)&args->content);
		free(args);
		args = tmp;
	}
	ft_memdel((void**)&args);
}

 static void free_it(t_it *it)
{
	ft_memdel((void**)&it->line);
	ft_memdel((void**)&it->tmp_line);
	ft_memdel((void**)&it->tmp_buffer);
	ft_memdel((void**)&it);
}

void free_list_and_struct(t_it *it, t_list *args)
{
  free_structure(args);
	free_it(it);
}

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
	*back = ft_strdup(it->line);
	free_structure(begin);
	free_it(it);
}
