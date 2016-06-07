#include <parse.h>

int	main(int argc, char **argv, char **env)
{
	if (argc == 2)
		parse(argv[1], env);
	return (0);
}
