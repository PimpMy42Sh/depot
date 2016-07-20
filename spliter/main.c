#include <spliter.h>

//gcc *.c -I. libft.a -g -Wall -Wextra

int					main(int argc, char **argv, char **env)
{
	char		*cmd = "/bin/ls -l | /bin/cat -e > out; /bin/cat < out";
	t_command	c;
	char		**split;

	split = ft_strsplit(cmd, ';');
	while (*split)
	{
		printf("(%s)\n", *split);
		if (**split)
		{
			c = get_next_command(&*split);
			exec_command(&c, env);
			ft_bzero(&c, sizeof(t_command));
			printf("=================\n");
		}
		split++;
	}
	return (0);
	(void)argc;
	(void)argv;
}
