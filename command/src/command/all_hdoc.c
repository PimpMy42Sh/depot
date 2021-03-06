#include <command.h>

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
	ft_putstr_fd(RED, 2);
	write(2, "Need an end string\n", 19);
	ft_putstr_fd(RESET, 2);
	free(eof);
	free(s);
	close(fd);
	return (1);
}

int						do_all_hdoc(char *cmd, char **env)
{
	t_it		*it;
	int			ok;

	ok = 0;
	it = ft_stock_it(0);
	nhdoc(0);
	while (*cmd)
	{
		if (*cmd == '<' && *(cmd + 1) == '<')
		{
			if (!ok)
			{
				go_to_bottom(it);
				ok = 1;
			}
			if (do_all_hdoc__normalize(&cmd, env))
			{
				print_prompt();
				return (1);
			}
		}
		else
			cmd++;
	}
	return (0);
}
