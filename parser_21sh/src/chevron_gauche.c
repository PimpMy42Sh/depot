#include <parse.h>

int		chevron_gauche(t_list *lst, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Open fails\n", 11);
		return (-1);
	}
	child = fork();
	if (child == -1)
	{
		write(2, "Fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		dup2(fd, STDIN_FILENO);
		ft_pipes(lst, environ);
	}
	close(fd);
	wait(NULL);
	return (0);
}

int		double_chevron_gauche(t_list *lst, char *filename, char **environ)
{
	int		fd;
	pid_t	child;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "Open fails\n", 11);
		return (-1);
	}
	child = fork();
	if (child == -1)
	{
		write(2, "Fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
	{
		dup2(fd, STDIN_FILENO);
		ft_pipes(lst, environ);
	}
	close(fd);
	wait(NULL);
	return (0);
}
