#include "../../include/minishell.h"
#include "../../include/command.h"

char			browse_skip_quote(char **s, char tmp)
{
	(*s)++;
	while (**s && **s != tmp)
		(*s)++;
	return (tmp);
}

static void		quote_reset(t_it *it)
{
	it->i = 0;
	it->buffer = 0;
	it->len = 0;
	ft_memdel((void**)&it->line);
	ft_memdel((void**)&it->tmp_line);
	ft_memdel((void**)&it->tmp_buffer);
	ft_putstr("\n> ");
}

static void		copy_first_element(char *begin, t_list **args)
{
	char	*tmp;

	tmp = ft_strjoin(begin, "\n");
	ft_lstadd_end(args, ft_lstnew(tmp, ft_strlen(tmp) + 1));
	ft_memdel((void**)&tmp);
}

static int		quotes_loop(t_it *it, t_list *args, char **back, char *end)
{
	t_ctrl_c	*ctrl_c;

	ctrl_c = ft_stock_ctrl_c(NULL);
	ctrl_c->bol = 0;
	ctrl_c->main_loop = 0;
	while (read(0, &it->buffer, 4))
	{
		if ((it->buffer == CTRL_D && !it->len) || !it->eof || ctrl_c->bol)
		{
			ctrl_c->bol = 0;
			free_list_and_struct(it, args);
			return (1);
		}
		parse_line(it);
		if (it->buffer == '\n')
		{
			if (!is_a_newline_quotes(it, end, &args))
				break ;
			quote_reset(it);
		}
		it->buffer = 0;
	}
	stop_quotes(it, ctrl_c, back, args);
	return (ctrl_c->main_loop);
}

int				quote_not_close(char *begin, char *end, char **back)
{
	t_it	*it;
	t_list	*args;

	args = NULL;
	copy_first_element(begin, &args);
	it = init_it_struct(1);
	it->eof = 1;
	ft_putstr("> ");
	resumed_terminal();
	return (quotes_loop(it, args, back, end));
}
