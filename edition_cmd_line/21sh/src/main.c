/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 11:36:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 13:43:28 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split_cmd_suite(int i, char **environ, char **cmd)
{
	int			status;

	g_father = fork();
	if (g_father > 0)
	{
		wait(&status);
		g_father = 0;
	}
	else
	{
		if (i == 0)
			ft_putchar('\n');
		parse_arguments(environ, cmd[i], 1);
	}
	resumed_terminal();
}

static void		split_cmd(t_it *it, char **environ)
{
	char				**cmd;
	int					i;
	static t_history	*history = NULL;

	i = 0;
	cmd = ft_strsplit(it->line, ';');
	history = create_elem(history, it->line);
	while (cmd[i])
	{
		if (!(check_line(cmd[i], environ, 0)))
			split_cmd_suite(i, environ, cmd);
		ft_memdel((void**)&it->line);
		i++;
	}
	if (!cmd[0])
		ft_putchar('\n');
	free_cmd(cmd);
	print_prompt();
}

static void		main_loop(char **environ)
{
	t_it			*it;

	it = init_it_struct();
	while (read(0, &it->buffer, 4))
	{
		parse_line(it);
		ft_stock_it(it);
		if (it->buffer == '\n')
		{
			check_only_space(it);
			if (it->line && ft_strlen(it->line))
				split_cmd(it, environ);
			else
			{
				ft_putchar('\n');
				print_prompt();
			}
			ft_memdel((void**)&it->line);
			it->i = 0;
		}
		it->buffer = 0;
	}
}

int				main(int argc, char **argv, char **environ)
{
	t_tty			*tty;

	(void)argv;
	(void)argc;
	tty = ft_memalloc(sizeof(struct s_tty));
	if (init_terminal_data(tty))
		return (-1);
	ft_stock_term(tty);
	check_shlvl(environ);
	print_prompt();
	check_signal();
	main_loop(environ);
	return (0);
}
