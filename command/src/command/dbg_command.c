#include <command.h>

void			free_command(t_command *c)
{
	if (c)
	{
		end_redirections(&c->redirs);
		free_double_array(c->argv);
		free(c);
	}
}

int				alloc_size(int len)
{
	static int			alloc_len = 0;

	if (len)
		alloc_len = len;
	return (alloc_len);
}

void			realloc_copy(char **s, char **str, int *len)
{
	*(*str + *len) = **s;
	(*s)++;
	(*len)++;
}
