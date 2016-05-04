/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_droite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:10:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/04 17:14:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		chevron_droite_filname(char *path, char **args, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "open fails\n", 11);
		return (-1);
	}
	
	child = fork();
	if (child == -1)
	{
		write(2, "open fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(path, args, environ);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		double_chevron_droite_filname(char *path, char **args, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "open fails\n", 11);
		return (-1);
	}
	child = fork();
	if (child == -1)
	{
		write(2, "fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(path, args, environ);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		run_pipe(char *path1, char **args1, char *path2, char **args2, char **environ)
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
		execve(path1, args1, environ);
	}
	dup2(pdes[PUSH_PIPE], STDIN_FILENO);
	close(pdes[PULL_PIPE]);
	wait(NULL);
	execve(path2, args2, environ);
	return (0);
}