#include <spliter.h>

int					more_pipe(int in, int out, t_list cmd, char **env)
{
	pid_t	pid;
	char	**tmp;

	tmp = cmd.content;
	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		execve(tmp[0], tmp, env);
	}
	return(pid);
}

int					ft_pipes(t_list cmds, char **env)
{
	t_list	*ptr;
	char	**tmp;
	int		in;
	int		fd[2];

	in = 0;
	ptr = &cmds;
	if (ptr)
		while (ptr->next)
		{
			pipe (fd);
			more_pipe (in, fd[1], *ptr, env);
			close (fd[1]);
			in = fd[0];
			ptr = ptr->next;
		}
	if (in != 0)
		dup2 (in, 0);
	tmp = ptr->content;
	return execvp(tmp[0], tmp);
}

void				exec_command(t_command *cmd, char **env)
{
	char			**tab;
	t_list			*pipes;
	t_list			*next;

	pipes = cmd->pipeline;
	do_redirections(3, &cmd->redirs);
	ft_pipes(*pipes, env);
	while (pipes)
	{
		next = pipes->next;
		tab = pipes->content;
		while (*tab)
		{
			printf("%s ", *tab);
			free(*tab);
			tab++;
		}
		free(pipes->content);
		free(pipes);
		pipes = next;
		printf("\n");
	}
	end_redirections(&cmd->redirs);
}
