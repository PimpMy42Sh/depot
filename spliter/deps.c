/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:49:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:49:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <spliter.h>

char	*ft_strword(char *s)
{
	int		index;
	char	*new_word;
	char	*cpy;

	new_word = 0;
	index = 0;
	cpy = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	cpy = s;
	while (*s != ' ' && *s != '\t' && *s)
	{
		index++;
		s++;
	}
	if ((new_word = ft_strnew(index)))
		ft_strncpy(new_word, cpy, index);
	return (new_word);
}

t_list	*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*lst;

	if ((lst = (t_list*)malloc(sizeof(t_list))))
	{
		lst->next = NULL;
		lst->content = cnt;
		lst->content_size = cnt_size;
	}
	else
		lst = NULL;
	return (lst);
}

int		ft_lstsize(t_list *t)
{
	int	n;

	n = 0;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}

void	delete_tab(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}
