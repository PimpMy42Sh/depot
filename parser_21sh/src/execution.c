#include <parse.h>

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

	child = fork();
	if (child == -1)
	{
		write(2, "Fork fails\n", 11);
		return (-1);
	}
	else if (child == 0)
		execve(path, args, environ);
	wait(NULL);
	return (0);
}
