//tail -f log

#include "../include/minishell.h"

void	debug(char *str, char buffer)
{
	t_it	*it;
	int		fd;
	char	*filename;

	filename = "log";
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	it = ft_stock_it(NULL);
	dprintf(fd, "\n---------------------\n");
	// dprintf(fd, "line = %d\n", line);
	// dprintf(fd, "itlen = %d\n", itlen);
	// dprintf(fd, "nb lines = %d\n", l);
	dprintf(fd, "i = %d\n", it->i);
	// dprintf(fd, "nb_lines = %d\n", it->nb_current_line);
	dprintf(fd, "str = %s\n", str);
	// dprintf(fd, "str2 = %s\n", str2);
	// dprintf(fd, "str3 = %s\n", str3);
	dprintf(fd, "buffer = %c\n", buffer);
	dprintf(fd, "---------------------\n");
	close(fd);
}
