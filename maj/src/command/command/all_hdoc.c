/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:50:46 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:50:48 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

static	int			skip_quotes_hdoc(char **s)
{
	int		tmp;
	int		index;

	index = 0;
	tmp = *((*s)++);
	while (**s != tmp && **s)
	{
		index++;
		(*s)++;
	}
	(*s)++;
	return (index + 2);
}

char				*ft_strword_hdoc(char **s)
{
	int		index;
	char	*new_word;
	char	*cpy;

	new_word = 0;
	index = 0;
	cpy = 0;
	while (**s == ' ')
		(*s)++;
	cpy = *s;
	while (**s != ' ' && **s != '|' && **s != '<' && **s != '>' && **s != ';' && **s)
	{
		if (**s == '\'' || **s == '\"')
			index += skip_quotes_hdoc(s);
		else
		{
			index++;
			(*s)++;
		}
	}
	new_word = ft_strnew(index + 2);
	if (index)
		ft_strncpy(new_word, cpy, index);
	return (new_word);
}

static void				error()
{
	ft_putstr_fd(RED, 2);
	write(2, "Need an end string\n", 19);
	ft_putstr_fd(RESET, 2);
}

static int				do_all_hdoc__normalize(char **cmd, char **env)
{
	char				*s;
	char				*eof;
	int					fd;
	int					ret;

	ret = 1;
	s = get_filename(nhdoc(1));
	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*cmd += 2;
	eof = ft_strword_hdoc(cmd);
	printf("{%s}\n", *cmd);
	if (*eof)
	{
		ft_strtrim_quotes(eof);
		printf("(%s)\n", eof);
		if (hdoc(eof, fd, s, env))
			return (1);
		ret = 0;
		write(1, "\n", 1);
	}
	else
		error();
	free(eof);
	free(s);
	close(fd);
	return (ret);
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
		else if (*cmd == '\'' || *cmd == '"')
			skip_quotes_hdoc(&cmd);
		else
			cmd++;
	}
	return (0);
}
