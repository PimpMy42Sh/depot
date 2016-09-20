#include <command.h>

int						nhdoc(int reset)
{
	static int			n = 0;

	if (reset)
		n++;
	else
		n = 0;
	return (n);
}

void					prepare_hdoc(t_redirection *r)
{
	char				*s;

	s = get_filename(nhdoc(1));
	r->fd = open(s, O_RDONLY);
	free(s);
}

char					*get_filename(int i)
{
	char				*i_to_a;
	char				*s;

	i_to_a = ft_itoa(i);
	s = ft_strjoin(HDOC_TMP_FILENAME, i_to_a);
	free(i_to_a);
	return (s);
}

void					hdoc__reset(t_it *it, int prompt)
{
	it->i = 0;
	it->buffer = 0;
	it->len = 0;
	ft_memdel((void**)&it->line);
	ft_memdel((void**)&it->tmp_line);
	if (prompt)
		ft_putstr("\n> ");
	else
		free(it);
}
