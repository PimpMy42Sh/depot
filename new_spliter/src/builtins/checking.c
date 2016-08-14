#include <minishell.h>

int					check_bultins(char **av, char **env)
{
	t_env			*e;

	e = malloc(sizeof(t_env));
	e->environ = env;
	if (!ft_strcmp(av[0], "exit"))
		ft_exit(av, e);
	else if (!ft_strcmp(av[0], "cd"))
		ft_cd(av, e);
	else if (!ft_strcmp(av[0], "setenv"))
		ft_setenv(av, e);
	else if (!ft_strcmp(av[0], "unsetenv"))
		ft_unsetenv(av, e);
	else if (!ft_strcmp(av[0], "env"))
	{
		ft_env(av, e->environ);
		resumed_terminal();
	}
	else
		return (0);
	free_double_array(av);
	return (1);
}

