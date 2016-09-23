/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:52:02 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:52:04 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

t_list			*get_pipeline(char **s, t_env *e)
{
	t_list		*cmds;
	t_command	*c;

	cmds = NULL;
	c = NULL;
	while (**s && **s != ';')
	{
		while (**s == ' ')
			(*s)++;
		if (!is_a_spec_char(**s) || is_a_redirection(*s))
			c = get_command(s, e);
		else if (**s == '|')
		{
			(*s)++;
			while (**s == ' ')
				(*s)++;
			ft_lstadd_end(&cmds, ft_lstnew_noalloc(c, sizeof(t_command)));
			c = NULL;
		}
	}
	if (c)
		ft_lstadd_end(&cmds, ft_lstnew_noalloc(c, sizeof(t_command)));
	return (cmds);
}
