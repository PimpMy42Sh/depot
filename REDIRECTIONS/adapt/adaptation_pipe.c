/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptation_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:10:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/04 17:14:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <adaptation.h>

/*
**	Execute une commande et delete argv
*/
int		exec_command(char *path, char **argv, char **env)
{
	int		ret;

	path = argv[0];
//	argv[0] = ft_strrchr(path, '/') + 1;
	//printf("%s\n", argv[0]);
	ret = -1;
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
		{
			ret = execve(path, argv, env);
		}
		else
			write(2, "Access Denied\n", 14);
	}
	else
		write(2, "Command not found\n", 18);
	free(argv);
	return (ret);
	(void)env;
	(void)ret;
}

/*
**	t : structure du terminal
**	pipe_op : liste des etats sur le maillon de l'operateur '|'
*/
int		run_pipe(t_term *t, char *path1, char *path2, t_dlist *pipe_op)
{
	int const	PUSH_PIPE 	= 0;
	int const	PULL_PIPE 	= 1;
	pid_t		child 		= -1;
	int			pdes[2];

	pipe(pdes);
	child = fork();
	if (child == -1)
	{
		close(pdes[PUSH_PIPE]);
		close(pdes[PULL_PIPE]);
		write(2, "fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		dup2(pdes[PULL_PIPE], STDOUT_FILENO);
		close(pdes[PUSH_PIPE]);
		exec_command(path1, get_last_argv(pipe_op), t->env);
	}
	dup2(pdes[PUSH_PIPE], STDIN_FILENO);
	close(pdes[PULL_PIPE]);
	wait(NULL);
	exec_command(path2, get_next_argv(pipe_op), t->env);
	return (0);
}
