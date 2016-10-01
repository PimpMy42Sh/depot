 #include <ft_glob.h>

static int		match_bracket(char *local, char *s, char *format, t_list **results)
{
	int		sign;
	int		ret;

	sign = 0;
	ret = 0;
	format++;
	if (*format == '!')
	{
		sign = 1;
		format++;
	}
	while (*format != ']' && *format)
	{
		if (!ret)
		{
			if (*(format + 1) == '-' && *(format + 2) != ']')
			{
				ret = (*format <= *s && *(format + 2) >= *s) != sign;
				format += 2;
			}
			else if ((*format == *s) != sign)
				ret = 1;
		}
		format++;
	}
	format += !!*format;
	return (ret && glob__match(local, s + 1, format, results));
}

static int		match_wildcard(char *local, char *s, char *format, t_list **results)
{
	char	*tmp;
	char	*occur;
	int		ret;
	int		ok;

	ok = 0;
	if (!*s)
		return (1);
	while (*format == '*')
		format++;
	if (!*format)
		return (1);
	ret = 0;
	tmp = (char*)s;
	if (*format == '/')
	{
		glob__open_directory(local, format + 1, 2, results);
		return 0;
	}
	if (*format != '[' && *format != ']' && *format != '?')
	{
		while ((occur = strchr(tmp, *format)))
		{
			ok = 1;
			ret = glob__match(local, occur, format, results);
			if (ret)
				return (1);
			tmp = occur + 1;
		}
		if (!ok)
			return (0);
		return (ret);
	}
	else
		return (glob__match(local, s + 1, format, results) ||
				glob__match(local, s, format, results));
}

int					glob__match(char *local, char *s, char *format, t_list **results)
{
	#ifdef DEBUG
//		printf("local = %s, s = %s, format = %s\n", local, s, format);
	#endif	

	if (!*s && !*format)
		return (1);
	else if (*format == '/')
		glob__open_directory(local, format + 1, 2, results);
	else if (*s == *format)
		return (glob__match(local, s + 1, format + 1, results));
	else if (*format == '*')
		return (match_wildcard(local, s, format, results));
	else if (*format == '?')
		return (glob__match(local, s + 1, format + 1, results));
	else if (*format == '[')
		return (match_bracket(local, s, format, results));
	return (0);
}
