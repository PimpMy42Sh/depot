#include "../../include/minishell.h"
#include "../../include/command.h"

static void	append_backlash_n(t_it *it, t_list **args)
{
	char	*tmp;

	tmp = ft_strjoin(it->line, "\n");
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp);
	ft_lstadd_end(args, ft_lstnew(it->line, ft_strlen(it->line) + 1));
	ft_memdel((void**)&tmp);
}

static int	is_a_newline(t_it *it, char end, t_list **args)
{
	int		delta;

	delta = (it->len + 2) / it->ws_col;
	move_begin(it);
	while (delta)
	{
		tputs(tgetstr(DOWN, NULL), 0, my_putchar);
		delta--;
	}
	if (it->line)
	{
		if (ft_strchr(it->line, end))
		{
			append_backlash_n(it, args);
			write(1, "\n", 1);
			return (0);
		}
		append_backlash_n(it, args);
	}
	else
		write(1, "\n", 1);
	return (1);
}

static void	quote_reset(t_it *it)
{
	it->i = 0;
	it->buffer = 0;
	it->len = 0;
	ft_memdel((void**)&it->line);
	ft_putstr("\n> ");
}

static void	copy_first_element(char *begin, t_list **args)
{
	char	*tmp;

	tmp = ft_strjoin(begin, "\n");
	ft_lstadd_end(args, ft_lstnew(tmp, ft_strlen(tmp) + 1));
	ft_memdel((void**)&tmp);
}

void		quote_not_close(char *begin, char end, char **back)
{
	t_it	*it;
	t_list	*args;

	args = NULL;
	copy_first_element(begin, &args);
	it = init_it_struct(1);
	it->eof = 1;
	ft_putstr("> ");
	resumed_terminal();
	while (read(0, &it->buffer, 4))
	{
		if ((it->buffer == CTRL_D && !it->len) || !it->eof)
			break ;
		parse_line(it);
		if (it->buffer == '\n')
		{
			if (!is_a_newline(it, end, &args))
				break ;
			quote_reset(it);
		}
		it->buffer = 0;
	}
	suspend_terminal();
	it->eof = 0;
	convert_it_line(it, args, back);
}
