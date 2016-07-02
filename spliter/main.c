#include <spliter.h>

//gcc *.c -I. -lft -g -Wall -Wextra

int					main(int argc, char **argv, char **env)
{
	char		*cmd = "/bin/ls -l | /bin/cat -e | /bin/cat -e > out";
	t_command	c;

	while (*cmd)
	{
		c = get_next_command(&cmd);
		printf("%s\n", cmd);
		printf("=================\n");
		if (c.pipeline)
			exec_command(&c, env);
		else
			ft_bzero(&c, sizeof(t_command));
	}
	return (0);
	(void)argc;
	(void)argv;
}
