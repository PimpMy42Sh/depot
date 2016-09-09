#include <command.h>
#include "../../include/minishell.h"

/*
**	Permet de determiner si on peux executer un ficher
*/

/*static int			test_access(char *name)
{
	DIR	*d;
	int	value;

	value = 0;
	if (!(d = opendir(name)))
	{
		if (!access(name, F_OK) && access(name, X_OK))
		{
			write(2, "Permission denied\n", 18);
			value = 1;
		}
	}
	else
		closedir(d);
	return (value);
}*/

static void			start_prgm(char **env, char **argv)
{
	if ((argv[0] = hash_cmd(argv[0], env)))
	{
		map_environ(env);
		execve(argv[0], argv, env);
	}
	command_not_find(argv[0]);
	exit(1);
}

static int    *open_pipes(int n_cmds)
{
	int     *pipes;
	int     i;

	pipes = (int*)malloc(sizeof(int) * ((n_cmds - 1) * 2));
	i = 0;
	while (i < (n_cmds - 1) * 2)
	{
		pipe(pipes + i);
		i += 2;
	}
	return (pipes);
}

static void   close_pipes(int *pipes, int n_cmds)
{
	int     i;

	i = 0;
	while (i < (n_cmds - 1) * 2)
	{
		if (pipes[i] > 2)
			close(pipes[i]);
		if (pipes[i + 1] > 2)
			close(pipes[i + 1]);
		i += 2;
	}
}

static int    recursive_execution(t_env *e, t_list *cmds, int *pipes, int n, int n_cmds)
{
	t_command *c;
	int     ret;

	ret = 0;
	if (cmds)
	{
		c = (t_command*)cmds->content;
		if (!fork())
		{
			if (!n) //connect 1 => pipes[1]
				dup2(pipes[1], STDOUT_FILENO);
			else if (n >= (n_cmds - 1) * 2) //last output => new_input
				dup2(pipes[n - 2], STDIN_FILENO);
			else //connect last output command => new input command
			{
				dup2(pipes[n - 2], STDIN_FILENO);
				dup2(pipes[n + 1], STDOUT_FILENO);
		}
		close_pipes(pipes, n_cmds);
		if (c->need_redir)
			do_redirections(&c->redirs, STDIN_FILENO, STDOUT_FILENO);
		start_prgm(e->environ, c->argv);
		}
		else
			ret = recursive_execution(e, cmds->next, pipes, n + 2, n_cmds);
	}
	return (ret + 1);
}


static void   execute_pipes(t_list *cmds, t_env *env)
{
	int     *pipes;
	int     n_cmds;
	int     i;
	int     n;

	i = 0;
	n_cmds = ft_lstsize(cmds);
	pipes = open_pipes(n_cmds);
	n = recursive_execution(env, cmds, pipes, 0, n_cmds);
	close_pipes(pipes, n_cmds);
	while (i <= n)
	{
	wait(NULL);
	i++;
	}
	free(pipes);
	exit(1);
}

void				execution(t_list *pipeline, t_env *e)
{
	t_command		*c;
	pid_t			p;

	if (pipeline && !verification_pipeline(pipeline))
	{
		if (pipeline->next)
		{
			if (!(p = fork()))
				execute_pipes(pipeline, e);
			wait(NULL);
		}
		else
		{
			c = pipeline->content;
			if (!check_bultins(c->argv, e))
			{
				if (!(p = fork()))
				{
					if (c->need_redir)
						do_redirections(&c->redirs, STDIN_FILENO, STDOUT_FILENO);
					start_prgm(e->environ, c->argv);
				}
				wait(NULL);
			}
		}
		wait(NULL);
	}

	t_list	*tmp;

	while (pipeline)
	{
		tmp = pipeline->next;
		free_command(pipeline->content);
		free(pipeline);
		pipeline = tmp;
	}
}
