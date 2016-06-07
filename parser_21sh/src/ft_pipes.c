#include <parse.h>

/*
**	Multipipe by ayoub
*/

static int	more_pipe(int in, int out, t_list **cmd, char **env)
{
	pid_t	pid;
	char	**tmp;

	tmp = lst_to_pipe_args(cmd);
	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		execve(tmp[0], tmp, env);
	}
	else if (pid == -1)
		write(2, "Fork fails\n", 11);
	free(tmp);
	return (pid);
}

/*
**	Suite de ft_pipes de ayoub
**	(remise a la norme)
*/

static void	do_pipe_process(t_list *cmds, char **env)
{
	int		in;
	int		fd[2];
	t_list	*ptr;
	char	**tmp;

	ptr = NULL;
	in = 0;
	tmp = NULL;
	ptr = get_last_cmd(cmds);
	while (cmds != ptr)
	{
		pipe(fd);
		more_pipe(in, fd[1], &cmds, env);
		close(fd[1]);
		in = fd[0];
	}
	if (in != 0)
		dup2(in, 0);
	tmp = lst_to_pipe_args(&cmds);
	if (test_command(tmp[0]))
		return ;
	execve(tmp[0], tmp, env);
	free(tmp);
}

/*
**	ft_pipes by ayoub
*/

int			ft_pipes(t_list *cmds, char **env)
{
	pid_t	child;

	child = 0;
	if (child == -1)
	{
		write(2, "Fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		do_pipe_process(cmds, env);
	}
	return (0);
}
