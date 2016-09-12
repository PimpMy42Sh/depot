#include <command.h>

void			print_command(t_command *c)
{
	char		**args;

	printf("==== %p ====\n", c);
	args = c->argv;
	while (*args)
	{
		printf("%s\n", *args);
		args++;
	}
	printf("(%d %d)\n", ft_lstsize(c->redirs.normal),
		ft_lstsize(c->redirs.agr));
}

void			free_command(t_command *c)
{
	if (c)
	{
		end_redirections(&c->redirs);
		free_double_array(c->argv);
		free(c);
	}
}
