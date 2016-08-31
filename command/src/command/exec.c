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

/*
**	Execute une commande
*/

void				exec_command(t_command *cmd, t_env *env)
{
	if (cmd->need_redir)
		do_redirections(0, &cmd->redirs);
	start_prgm(*env, cmd->argv);
}

/*
**	By ayoub
*/

static int			more_pipe(int in, int out, t_list *cmd, t_env *env)
{
	pid_t			pid;

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
		exec_command((t_command*)cmd->content, env);
	}
	return (WEXITSTATUS(&pid));
}

/*
**	By ayoub
*/

int					ft_pipes(t_list *cmds, int child, t_env *env)
{
	int				in;
	int				fd[2];

	in = 0;
	while (cmds->next)
	{
		pipe(fd);
		more_pipe(in, fd[1], cmds, env);
		close(fd[1]);
		in = fd[0];
		cmds = cmds->next;
	}
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	exec_command((t_command*)cmds->content, env);
	return (WEXITSTATUS(&child));
}

void				execution(t_list *pipeline, t_env *e)
{
	t_command		*c;
	pid_t			p;

	if (pipeline)
	{
		if (pipeline->next)
		{
			if (!(p = fork()))
				ft_pipes(pipeline, p, e);
			wait(NULL);
		}
		else
		{
			c = pipeline->content;
			if (!check_bultins(c->argv, e))
			{
				if (!(p = fork()))
					exec_command(c, e);
				wait(NULL);
			}
		}
	}
	wait(NULL);

	t_list	*tmp;

	while (pipeline)
	{
		tmp = pipeline->next;
		free_command(pipeline->content);
		free(pipeline);
		pipeline = tmp;
	}
}