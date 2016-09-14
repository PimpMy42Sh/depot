/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:15:22 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/14 15:24:20 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/command.h"

static void	split_cmd(t_it *it, t_env *env)
{
	char				*s;
	t_list				*c;
	static t_history	*history = NULL;
	char				*back;

	back = NULL;
	ft_putchar('\n');
	history = create_elem(history, it->line);
	s = it->line;
	if (check_line_quotes(s, &back) || do_all_hdoc(s, env->environ))
		return ;
	if (back)
		s = back;
	nhdoc(0);
	while (*s)
	{
		while ((c = get_pipeline(&s, env)))
		{
			execution(c, env);
			s += (*s == ';');
		}
		s += (*s == ';');
	}
}

static void	parse(t_it *it, t_env *env)
{
	t_ctrl_c	*ctrl_c;

	ctrl_c = ft_stock_ctrl_c(NULL);
	suspend_terminal();
	ctrl_c->stdin = 0;
	split_cmd(it, env);
	ft_memdel((void**)&it->line);
	resumed_terminal();
	if (!ctrl_c->stdin)
		print_prompt();
	ctrl_c->stdin = 1;
	ctrl_c->bol = 0;
}

static void	main_loop(t_env *env)
{
	t_it			*it;
	t_ctrl_c	*ctrl_c;

	it = init_it_struct(0);
	ctrl_c = ft_stock_ctrl_c(NULL);
	while (read(0, &it->buffer, 4))
	{
		ctrl_c->stdin = 0;
		parse_line(it);
		ft_stock_it(it);
		if (it->buffer == '\n')
		{
			check_only_space(it);
			if (it->line && ft_strlen(it->line))
				parse(it, env);
			else
			{
				go_to_bottom(it);
				ft_putchar('\n');
				if (!ctrl_c->stdin)
					print_prompt();
			}
			ft_memdel((void**)&it->line);
			it->i = 0;
			it->len = 0;
		}
		it->buffer = 0;
	}
}

static void	init_copy_environ(t_env *env, char **environment)
{
	int		i;

	if (!environment[0])
	{
		env->environ = (char**)ft_memalloc(sizeof(char*));
		path_manager(env);
		return ;
	}
	i = return_env_size(environment);
	env->environ = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (environment[i])
	{
		env->environ[i] = ft_strdup(environment[i]);
		i++;
	}
	env->environ[i] = NULL;
	if ((i = return_env_indice(env->environ, "PATH")) == -1)
		path_manager(env);
}

int			main(int argc, char **argv, char **environment)
{
	t_tty			*tty;
	t_env			*env;
	t_ctrl_c	*ctrl_c;

	(void)argv;
	(void)argc;
	ctrl_c = (t_ctrl_c*)ft_memalloc(sizeof(struct s_ctrl_c));
	ft_bzero(ctrl_c, sizeof(t_ctrl_c));
	ft_stock_ctrl_c(ctrl_c);
	env = (t_env*)ft_memalloc(sizeof(struct s_env));
	init_copy_environ(env, environment);
	parse_path_directories(env->environ);
	tty = (t_tty*)ft_memalloc(sizeof(struct s_tty));
	if (init_terminal_data(tty))
		return (-1);
	ft_stock_term(tty);
	check_shlvl(env);
	print_prompt();
	check_signal();
	main_loop(env);
	return (0);
}
