#include <command.h>
#include "../../include/minishell.h"

static int		test_access(char *name)
{
	DIR				*d;
	int				ret;

	ret = 0;
	ft_putstr_fd(RED, 2);
	if ((d = opendir(name)))
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		write(2, "Is a directory\n", 15);
		ret = 1;
		closedir(d);
	}
	else if (!access(name, F_OK))
		if (access(name, X_OK))
		{
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			write(2, "Permission denied\n", 18);
			ret = 1;
		}
	ft_putstr_fd(RESET, 2);
	return (ret);
}

void			start_prgm(char **env, char **argv)
{
	if (test_access(argv[0]))
		exit(1);
	if (!ft_strncmp("./", argv[0], 2))
		execve(argv[0] + 2, argv, env);
	else if ((argv[0] = hash_cmd(argv[0], env)))
		execve(argv[0], argv, env);
	command_not_find(argv[0]);
	exit(1);
}

void			stop_cmd(t_list *pipeline)
{
	t_list	*tmp;

	while (pipeline)
	{
		tmp = pipeline->next;
		free_command(pipeline->content);
		free(pipeline);
		pipeline = tmp;
	}
}

int				execution__simple_command(t_command *c, t_env *e)
{
	pid_t			p;

	if (!check_bultins(c, e) && !(p = fork()))
	{
		if (c->need_redir)
			do_redirections(&c->redirs, STDIN_FILENO, STDOUT_FILENO);
		start_prgm(e->environ, c->argv);
	}
	wait(NULL);
	return (WEXITSTATUS(p));
}

int				execution(t_list *pipeline, t_env *e)
{
	int		ret;
	pid_t	p;

	ret = 0;
	g_father = 0;
	if (pipeline && !verification_pipeline(pipeline))
	{
		if (pipeline->next)
		{
			if (!(p = fork()))
				execute_pipes(pipeline, e);
			wait(NULL);
			ret = WEXITSTATUS(p);
		}
		else
			ret = execution__simple_command(pipeline->content, e);
		wait(NULL);
	}
	g_father = 1;
	return (ret);
}
