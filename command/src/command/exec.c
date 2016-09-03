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
**	By ayoub
*/

static int			more_pipe(int in, int out, t_command *cmd, t_env *env)
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
		start_prgm(env->environ, cmd->argv);
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
	t_command		*c;

	in = 0;
	while (cmds->next)
	{
		pipe(fd);
		c = cmds->content;
//		print_command(c);
		if (c->need_redir)
			do_redirections(0, &c->redirs, in, fd[1]);
		more_pipe(in, fd[1], c, env);
		close(fd[1]);
		in = fd[0];
		cmds = cmds->next;
	}
	c = cmds->content;
//	print_command(c);
	if (c->need_redir)
		do_redirections(0, &c->redirs, in, STDOUT_FILENO);
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	start_prgm(env->environ, c->argv);
	return (WEXITSTATUS(&child));
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
				ft_pipes(pipeline, p, e);
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
						do_redirections(0, &c->redirs, 0, 1);
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