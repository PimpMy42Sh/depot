#include <minishell.h>

static void			print_string(char **av, char **environ, int delta)
{
	int				i;
	int				ok;

	ok = 0;
	i = delta;
	check_tilde_and_dollar(environ, av, 0);
	while (av[i])
	{
		ft_putstr(av[i]);
		if (*av[i])
			ok = 1;
		if (ok && av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (delta != 2)
		ft_putchar('\n');
}

void				ft_echo(char **av, char **environ)
{
	if (!av[1])
		ft_putchar('\n');
	else if (av[1] && !ft_strcmp(av[1], "-n") && !av[2])
		return ;
	else if (av[1] && !ft_strcmp(av[1], "-n") && av[2])
		print_string(av, environ, 2);
	else
		print_string(av, environ, 1);
}
