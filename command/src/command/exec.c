#include <command.h>
#include "../../include/minishell.h"

void				start_prgm(char **env, char **argv)
{
	if ((argv[0] = hash_cmd(argv[0], env)))
	{
		map_environ(env);
		execve(argv[0], argv, env);
	}
	command_not_find(argv[0]);
	exit(1);
}

static void			stop_cmd(t_list *pipeline)
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

int						execution__simple_command(t_command *c, t_env *e)
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

int					execution(t_list *pipeline, t_env *e)
{
	int		ret;
	pid_t	p;

	ret = 0;
	if (pipeline && !verification_pipeline(pipeline))
	{
		if (pipeline->next)
		{
			if (!(g_father = fork()))
				execute_pipes(pipeline, e);
			wait(NULL);
			ret = WEXITSTATUS(p);
		}
		else
		{
			g_father = 0;
			ret = execution__simple_command(pipeline->content, e);
			g_father = 1;
		}
		wait(NULL);
	}
	stop_cmd(pipeline);
	return (ret);
}
