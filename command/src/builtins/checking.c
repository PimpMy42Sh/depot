#include <minishell.h>
#include <command.h>

static void					do_bultins(char **av, t_env *env)
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
		ft_env(av, env->environ);
	else
		ft_echo(av, env->environ);
}

static void					builtins_redirs(t_command *c, t_env *e)
{
	if (!fork())
	{
		do_redirections(&c->redirs, 0, 1);
		do_bultins(c->argv, e);
		exit(1);
	}
}

static int					is_a_builtin(char *av)
{
	return (!ft_strcmp(av, "exit")
			|| !ft_strcmp(av, "cd")
			|| !ft_strcmp(av, "setenv")
			|| !ft_strcmp(av, "unsetenv")
			|| !ft_strcmp(av, "env")
			|| !ft_strcmp(av, "echo"));
}

int							check_bultins(t_command *c, t_env *e)
{
	if (is_a_builtin(c->argv[0]))
	{
		if (c->need_redir)
			builtins_redirs(c, e);
		else
			do_bultins(c->argv, e);
		return (1);
	}
	return (0);
}
