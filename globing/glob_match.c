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
		sign = !sign;
		format++;
	}
	while (*format != ']')
	{
		if (!ret)
		{
			if (*(format + 1) == '-')
			{
				ret = *format <= *s && *format >= *s;
				format++;
			}
			else if ((*format == *s) != sign)
				ret = 1;
		}
		format++;
	}
	format++;
	return (ret && glob__match(s + 1, format));
}

static int		match_wildcard(const char *s, const char *format)
{
	char	*ret;

	if (!*s)
		return (1);
	while (*format == '*')
		format++;
	if (!*format)
		return (1);
	ret = strchr(s, *format);
	if (ret)
		return (glob__match(ret, format));
	return (1);
}

int					glob__match(const char *s, const char *format)
{
	#ifdef DEBUG
//		printf("s = %s, format = %s\n", s, format);
	#endif	

	if (!s)
		return (0);
	else if (!*s && !*format)
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
