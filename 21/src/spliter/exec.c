#include <spliter.h>
#include "../../include/minishell.h"

/*
**	Permet de determiner si on peux executer un ficher
*/

static int			test_access(char *name)
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
}

/*
**	Execute un programme
**
**	En premier lieu, il faut ajouter la gestion du path
*/

static int			start_prgm(char **env, char **argv, int child)
{
	if (test_access(argv[0]))
		return (0);
	else
	{
		check_tilde_and_dollar(env, argv, 1);
		argv[0] = hash_cmd(argv[0], env);
		map_environ(env);
		suspend_terminal();
		execve(argv[0], argv, env);
		command_not_find(argv[0]);
		exit(1);
	}
	return (WEXITSTATUS(child));
}

/*
**	By ayoub
*/

static int			more_pipe(int in, int out, t_list *cmd, char **env)
{
	pid_t	pid;

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
		start_prgm(env, (char**)cmd->content, pid);
	}
	return (pid);
}

/*
**	By ayoub
*/

static int			ft_pipes(t_list *cmds, int child, char **env)
{
	int		in;
	int		fd[2];

	in = 0;
	if (cmds)
	{
		while (cmds->next)
		{
			pipe(fd);
			more_pipe(in, fd[1], cmds, env);
			close(fd[1]);
			in = fd[0];
			cmds = cmds->next;
		}
		if (in != 0)
			dup2(in, 0);
		start_prgm(env, (char**)cmds->content, child);
	}
	return (0);
}

/*
**	Execute une commande
*/
void				exec_command(t_command *cmd, t_env *env)
{
	t_list			*pipes;
	t_list			*next;
	pid_t			child;

	if ((pipes = cmd->pipeline))
	{
		if (!cmd->need_redir)
			pipes = check_bultins_command(pipes, env);
		if (pipes && !(child = fork()))
		{
			if (cmd->need_redir)
				do_redirections(0, &cmd->redirs);
			ft_pipes(pipes, child, env->environ);
			while (pipes)
			{
				next = pipes->next;
				delete_tab((char**)pipes->content);
				free(pipes);
				pipes = next;
			}
			if (cmd->need_redir)
				end_redirections(&cmd->redirs);
		}
		wait(NULL);
	}
}
