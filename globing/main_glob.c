#include <ft_glob.h>
#include <glob.h>

int		process__glob_sys(char *s2)
{
	glob_t	g;
	char	**r;
	int		i;

	i = 0;
	glob(s2, 0, 0, &g);
	#ifdef DEBUG

	if ((r = g.gl_pathv))
	while (r[i])
	{
//			printf("%s\n", r[i]);
		i++;
	}
	#endif
	i = g.gl_pathc;
	globfree(&g);
	return (i);
}

int		process__glob_ft(char **paths, char *s1)
{
	char	*s;
	int		i;
	s = ft_strdup("\0");
	ft_glob(paths, &s, s1);
	#ifdef DEBUG
//		printf("%s\n", s);
	#endif
	i = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			i++;
			while (*s != ' ')
				s++;
		}
		else
			s++;
	}
	return (i);
}

int		process(char *s1)
{
	int	ret_sys;
	int	ret_ft;
	char	*paths[1];

	paths[0] = "./";
	paths[1] = NULL;

	ret_ft = process__glob_ft(paths, s1);
	#ifdef DEBUG
		printf("ft: %d", ret_ft);
	#endif

	ret_sys = process__glob_sys(s1);
	#ifdef DEBUG
		printf("|sys: %d\n", ret_sys);
	#endif

	return (ret_ft == ret_sys);
}

int		main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc == 2)
	{
		ret = process(argv[1]);
		#ifdef DEBUG
			printf("<%s> %d\n", argv[1], ret);
		#endif
	}
	else
		printf("Bad args\n");
	return (ret);
}