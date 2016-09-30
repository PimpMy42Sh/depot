 #include <ft_glob.h>

static int		match_bracket(const char *s, const char *format)
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
	return (ret && glob__match(s + 1, format));
}

static int		match_wildcard(const char *s, const char *format)
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
	while ((occur = strchr(tmp, *format)))
	{
		ok = 1;
		ret = glob__match(occur, format);
		if (ret)
			return (1);
		tmp = occur + 1;
	}
	if (!ok)
		return (0);
	return (ret);
}

int					glob__match(const char *s, const char *format)
{
	#ifdef DEBUG
		printf("s = %s, format = %s\n", s, format);
	#endif	

	if (!*s && !*format)
		return (1);
	else if (*s == *format)
		return (glob__match(s + 1, format + 1));
	else if (*format == '*')
		return (match_wildcard(s, format));
	else if (*format == '?')
		return (glob__match(s + 1, format + 1));
	else if (*format == '[')
		return (match_bracket(s, format));
	else
		return (0);
}
