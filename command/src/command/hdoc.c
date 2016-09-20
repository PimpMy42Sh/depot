#include "../../include/minishell.h"
#include <command.h>

static int				is_a_newline(t_it *it, int fd, char *eof, char **env)
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
		if (!ft_strcmp(it->line, eof))
			return (0);
		check_tilde_and_dollar__str(env, &it->line);
		ft_putendl_fd(it->line, fd);
	}
	else
		write(fd, "\n", 1);
	return (1);
}

static void				put_back(t_it *it, int fd, char *s, int bol)
{
	if (bol)
		suspend_terminal();
	it->eof = 0;
	hdoc__reset(it, 0);
	close(fd);
	if (s)
		ft_memdel((void**)&s);
}

static int				hdoc__kill(char *eof, t_ctrl_c *ctrl_c)
{
	free(eof);
	ctrl_c->bol = 0;
	return (1);
}

static void				hdoc__start(t_it **it, t_ctrl_c **ctrl_c)
{
	*ctrl_c = ft_stock_ctrl_c(NULL);
	(*ctrl_c)->bol = 0;
	*it = init_it_struct(1);
	(*it)->eof = 1;
	ft_putstr("> ");
	resumed_terminal();
}

int						hdoc(char *eof, int fd, char *s, char **env)
{
	t_it			*it;
	t_ctrl_c		*ctrl_c;

	hdoc__start(&it, &ctrl_c);
	while (read(0, &it->buffer, 4))
	{
		if ((it->buffer == CTRL_D && !it->len))
			break ;
		if (!it->eof || ctrl_c->bol)
		{
			put_back(it, fd, s, 0);
			return (hdoc__kill(eof, ctrl_c));
		}
		parse_line(it);
		if (it->buffer == '\n')
		{
			if (!is_a_newline(it, fd, eof, env))
				break ;
			hdoc__reset(it, 1);
		}
		it->buffer = 0;
	}
	put_back(it, fd, NULL, 1);
	return (0);
}
