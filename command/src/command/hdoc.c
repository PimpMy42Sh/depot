#include "../../include/minishell.h"
#include <command.h>

static void				hdoc__reset(t_it *it, int prompt)
{
	it->i = 0;
	it->buffer = 0;
	it->len = 0;
	ft_memdel((void**)&it->line);
	ft_memdel((void**)&it->tmp_line);
	if (prompt)
		ft_putstr("\n> ");
	else
		free(it);
}

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

static void 			put_back(t_it *it, int fd, char *s, int bol)
{
	if (bol)
		suspend_terminal();
	it->eof = 0;
	hdoc__reset(it, 0);
	close(fd);
	if (s)
		ft_memdel((void**)&s);
}

static int				hdoc(char *eof, int fd, char *s, char **env)
{
	t_it			*it;
	t_ctrl_c	*ctrl_c;

	ctrl_c = ft_stock_ctrl_c(NULL);
	ctrl_c->bol = 0;
	it = init_it_struct(1);
	it->eof = 1;
	ft_putstr("> ");
	resumed_terminal();
	while (read(0, &it->buffer, 4))
	{
		if ((it->buffer == CTRL_D && !it->len))
			break ;
		if (!it->eof || ctrl_c->bol)
		{
			put_back(it, fd, s, 0);
			free(eof);
			ctrl_c->bol = 0;
			return (1);
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

static int				do_all_hdoc__normalize(char **cmd, char **env)
{
	char				*s;
	char				*eof;
	int					fd;

	s = get_filename(nhdoc(1));
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*cmd += 2;
	eof = ft_strword(*cmd);
	if (*eof)
	{
		if (hdoc(eof, fd, s, env))
			return (1);
		write(1, "\n", 1);
		free(eof);
		free(s);
		close(fd);
		return (0);
	}
	write(2, "Need an end string\n", 19);
	free(eof);
	free(s);
	close(fd);
	return (1);
}

int						do_all_hdoc(char *cmd, char **env)
{
	nhdoc(0);
	while (*cmd)
	{
		if (*cmd == '<' && *(cmd + 1) == '<')
		{
			if (do_all_hdoc__normalize(&cmd, env))
				return (1);
		}
		else
			cmd++;
	}
	return (0);
}
