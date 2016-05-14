/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptation_chevron_droite.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:10:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/04 17:14:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <adaptation.h>

/*
**	t: structure du mshell	
**	path : chemin
**	args : get_arguments()
**	r: permet de recuperer un fd
*/
int		chevron_droite(t_term *t, char *path, char **args, t_redirection *r)
{
	int		fd;
	pid_t	child;

	path = args[0];
	fd = open_redirection(r, O_WRONLY | O_CREAT | O_TRUNC);
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
		execve(path, args, t->env);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		double_chevron_droite(t_term *t, char *path, char **args, t_redirection *r)
{
	int		fd;
	pid_t	child;

	path = args[0];
	fd = open_redirection(r, O_WRONLY | O_CREAT | O_APPEND);
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
		execve(path, args, t->env);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		chevron_droite_filename(t_term *t, char *path, char **args, char *filename)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
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
		execve(path, args, t->env);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		double_chevron_droite_filename(t_term *t, char *path, char **args, char *filename)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
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
		execve(path, args, t->env);
	}
	close(fd);
	wait(NULL);
	return (0);
}