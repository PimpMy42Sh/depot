#include "../../include/minishell.h"
#include <command.h>


/*
**	J'ouvre un fd et le ferme pour sauvegarder son contenu
*/

static int				is_a_newline(t_it *it, int fd, char *eof)
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
		ft_putendl_fd(it->line, fd);
	}
	else
		write(fd, "\n", 1);
	return (1);
}

static void				hdoc(char *eof, int fd)
{
	t_it			*it;

	it = init_it_struct();
	it->eof = 1;
	ft_putstr("> ");
	while (read(0, &it->buffer, 4))
	{
		if ((it->buffer == CTRL_D && !it->len) || !it->eof)
			break ;
		parse_line(it);
		if (it->buffer == '\n')
		{
			if (!is_a_newline(it, fd, eof))
				break ;
			it->i = 0;
			it->buffer = 0;
			it->len = 0;
			it->line = 0;
			ft_putstr("\n> ");
		}
		it->buffer = 0;
	}
	it->eof = 0;
	close(fd);
}

/*
**	faire tout les eofs d'un coup
*/
void					do_all_hdoc(char *cmd)
{
	int		fd;
	char	*eof;

	while (*cmd)
	{
		if (*cmd == '<' && *(cmd + 1) == '<')
		{
			fd = open(HDOC_TMP_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
			cmd += 2;
			eof = ft_strword(cmd);
			hdoc(eof, fd);
			free(eof);
		}
		else
			cmd++;
	}
}

void					prepare_hdoc(t_redirections *t, t_redirection *r)
{
	r->fd = open(HDOC_TMP_FILENAME, O_RDWR | O_RDONLY);
	write(1, "\n", 1);
	ft_lstadd(&t->in, ft_lstnew_noalloc(r, sizeof(t_redirection)));
}
