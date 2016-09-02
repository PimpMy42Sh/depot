#include <minishell.h>

int					check_bultins(char **av, t_env *env)
{
	if (!ft_strcmp(av[0], "exit"))
		ft_exit(av, env);
	else if (!ft_strcmp(av[0], "cd"))
		ft_cd(av, env);
	else if (!ft_strcmp(av[0], "setenv"))
		ft_setenv(av, env);
	else if (!ft_strcmp(av[0], "unsetenv"))
		ft_unsetenv(av, env);
	else if (!ft_strcmp(av[0], "env"))
	{
		ft_env(av, env->environ);
		resumed_terminal();
	}
	else if (!ft_strcmp(av[0], "echo"))
		ft_echo(av, env->environ);
	else
		return (0);
	return (1);
}
