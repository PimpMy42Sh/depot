/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:32:04 by Marco             #+#    #+#             */
/*   Updated: 2016/07/19 11:58:28 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			    return_offset(void)
{
	char		*cwd;
	char		buffer[256];
	int			offset;

	offset = 0;
	cwd = NULL;
	cwd = getcwd(buffer, 256);
	if (cwd)
		offset = ft_strlen(cwd);
	return (offset + 2);
}

static char		*copy_end_line(int j, int i, char *line)
{
	int		k;
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * (ft_strlen(line) + 1));
	k = 0;
	while (line[j])
	{
		if (j >= i)
		{
			tmp[k] = line[j];
			k++;
		}
		j++;
	}
	tmp[k] = 0;
	return (tmp);
}

void		    replace_char(t_it *it, char cmd[2])
{
	int		size;
	char	*tmp2;
	char	*tmp3;
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_memalloc(sizeof(char) * (it->i + 3));
	ft_strncpy(tmp, it->line, it->i);
	tmp[it->i + 1] = '\0';
	tmp = ft_strcat(tmp, cmd);
	tmp3 = copy_end_line(j, it->i, it->line);
	tmp2 = ft_strjoin(tmp, tmp3);
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp2);
	multi_line_text(it);
	size = ((it->len + 1) + it->offset) + 1;
	if (!(size % (it->ws_col)))
		tputs(tgetstr(RIGHT, NULL), 0, my_putchar);
	free_elements(tmp, tmp2, tmp3, NULL);
}
