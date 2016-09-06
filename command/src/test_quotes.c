#include "../include/minishell.h"
#include <stdio.h>
# define QUOTES			'\''
# define D_QUOTES		'"'
# define B_QUOTES		'`'
# define PARENTHESES	'('
# define C_PARENTHESES	')'
# define ACCOLADES 		'{'
# define C_ACCOLADES 	'}'
# define CROCHETS 		'['
# define C_CROCHETS 	']'
# define BAD_QUOTES 	1
# define BAD_D_QUOTES	2
# define BAD_B_QUOTES	3
# define BAD_PARENTHESE	4
# define BAD_ACCOLADES	5
# define BAD_CROCHETS 	6
# define SYNTAX_ERROR 	7

void		skip_quote(char **s, char eof)
{
	while (**s && **s != eof)
		(*s)++;
}

int			check_line_is_close(char **s, t_list **lst)
{
	int		compteur;
	int		value;
	char	*tmp;

	compteur = 0;
	while (**s)
	{
		if (**s == '"' || **s == '\'')
		{
			tmp = *s;
			(*s)++;
			skip_quote(s, *tmp);
			if (!**s)
			{
				*s = tmp;
				ft_lstadd(lst, ft_lstnew(tmp, sizeof(char)));
			}
			(*s)++;
		}
		else if (**s == '(')
		{
			compteur++;
			(*s)++;
		}
		else if (**s == ')')
		{
			compteur--;
			(*s)++;
		}
		else
			(*s)++;
		if (compteur < 0)
			return (SYNTAX_ERROR);
	}
	if (compteur)
		ft_lstadd(lst, ft_lstnew("(", sizeof(char)));
	return (0);
}

int			create_list(char *s, t_list **tmp)
{
	int		ret;

	*tmp = NULL;
	while (*s && (ret = check_line_is_close(&s, tmp)) != 0)
		s++;
	return (0);
}

void	dbg(char *s)
{
	t_list	*lst;
	int		ret;

	if ((ret = create_list(s, &lst)) != SYNTAX_ERROR)
	{
		while (lst)
		{
			printf("%c\n", *(char*)lst->content);
			lst = lst->next;
		}
	}
	else
		printf("ERROR\n");
}

int		main()
{
	char	*s = "\'\"()\"";
	dbg(s);
	return (0);
}