#include <ft_glob.h>

int		main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc == 3)
	{
		ret = glob__match(argv[1], argv[2]);
		#ifdef DEBUG
			printf("<%s, %s> %d\n", argv[1], argv[2], ret);
		#endif
	}
	else
		printf("Bad args\n");
	return (ret);
}
