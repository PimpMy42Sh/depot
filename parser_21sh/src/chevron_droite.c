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

# include <parse.h>

int		chevron_gauche(char *path, char **args, char *filename, char **environ)
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
		dup2(fd, STDIN_FILENO);
		execve(path, args, environ);
	}
	close(fd);
	wait(NULL);
	return (0);
}


int		chevron_droite(char *path, char **args, char *filename, char **environ)
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

int		test_command(char *path)
{
	if (!access(path, F_OK))
	{
		if (access(path, X_OK))
		{
			write(2, "Permission denied\n", 18);
			return (PERMISSION_DENIED);
		}
	}
	else
	{
		write(2, "Command not found\n", 18);
		return (COMMAND_NOT_FOUND);
	}
	return (0);
}

int		execute_cmd(char *path, char **args, char **environ)
{
	pid_t	child;

	if (test_command(path))
		return (-1);
	child = fork();
	if (child == -1)
	{
		write(2, "fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
		execve(path, args, environ);
	wait(NULL);
	return (0);
}

int		double_chevron_droite(char *path, char **args, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	if (test_command(path))
		return (-1);
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

int		double_chevron_gauche(char *path, char **args, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	if (test_command(path))
		return (-1);
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
		dup2(fd, STDIN_FILENO);
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

	if (test_command(path1) || test_command(path2))
		return (-1);
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

int main(int argc, char **argv, char **env)
{
	if (argc == 2)
		parse(argv[1], env);
	else
		printf("parser test\n");
	return (0);
}