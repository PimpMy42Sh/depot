#include <command.h>

static int			*open_pipes(int n_cmds)
{
	int				*pipes;
	int				i;

	pipes = (int*)malloc(sizeof(int) * ((n_cmds - 1) * 2));
	i = 0;
	while (i < (n_cmds - 1) * 2)
	{
		pipe(pipes + i);
		i += 2;
	}
	return (pipes);
}

static void			close_pipes(int *pipes, int n_cmds)
{
	int				i;

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

static void			process_execution(void **norme_it,
					int *pipes, int n, int n_cmds)
{
	t_command	*c;

	c = (t_command*)((t_list*)norme_it[0])->content;
	if (!n)
		dup2(pipes[1], STDOUT_FILENO);
	else if (n >= (n_cmds - 1) * 2)
		dup2(pipes[n - 2], STDIN_FILENO);
	else
	{
		dup2(pipes[n - 2], STDIN_FILENO);
		dup2(pipes[n + 1], STDOUT_FILENO);
	}
	close_pipes(pipes, n_cmds);
	if (c->need_redir)
		do_redirections(&c->redirs, STDIN_FILENO, STDOUT_FILENO);
	start_prgm(((t_env*)norme_it[1])->environ, c->argv);
}

static int			recursive_execution(void **norme_it,
					int *pipes, int n, int n_cmds)
{
	int				ret;
	t_list			*cmds;

	ret = 0;
	cmds = (t_list*)norme_it[0];
	if (cmds)
	{
		if (!fork())
			process_execution(norme_it, pipes, n, n_cmds);
		else
		{
			norme_it[0] = ((t_list*)norme_it[0])->next;
			ret = recursive_execution(norme_it, pipes, n + 2, n_cmds);
		}
	}
	return (ret + 1);
}

void				execute_pipes(t_list *cmds, t_env *env)
{
	int				*pipes;
	int				n_cmds;
	int				i;
	int				n;
	void			*norme_it[2];

	norme_it[0] = cmds;
	norme_it[1] = env;
	i = 0;
	n_cmds = ft_lstsize(cmds);
	pipes = open_pipes(n_cmds);
	n = recursive_execution(norme_it, pipes, 0, n_cmds);
	close_pipes(pipes, n_cmds);
	while (i <= n)
	{
		wait(NULL);
		i++;
	}
	free(pipes);
	exit(1);
}
