/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptation_chevron_droite.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:10:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/04 17:14:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <adaptation.h>

/*
**	Rembodine la liste jusqu'au dernier mot trouver
**	Renvoie le nombre de iteration
*/
int	rewind_cmd(t_dlist **ptr)
{
	t_lexer_item	*it;
	t_dlist			*dl;
	int				cur;

	cur = 0;
	dl = *ptr;
	while (dl)
	{
		it = (t_lexer_item*)dl->content;
		if (it->type == IS_WORD)
		{
			cur++;
			dl = dl->last;
		}
		else
			break ;
	}
	*ptr = dl;
	return (cur);
}

/*
**	Retourne un argv pour la commande avant un pipe
*/
char	**get_last_argv(t_dlist *dl)
{
	char	**argv;
	int		size;
	int		i;
	t_word	*w;

	size = 1;
	dl = dl->last;
	while (dl && dl->last && ((t_lexer_item*)dl->content)->type == IS_WORD)
	{
		size++;
		dl = dl->last;
	}
	argv = (char**)malloc(sizeof(char*) * (size + 1));
	argv[size] = NULL;
//	printf("last size %d\n", size);
	i = 0;
	while (i < size && dl)
	{
		w = ((t_lexer_item*)dl->content)->word;
		argv[i] = w->token;
		argv[i + 1] = NULL;
		dl = dl->next;
//		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
	return (argv);
}

/*
**	Retourne un argv pour la commande apres un pipe
*/
char	**get_next_argv(t_dlist *dl)
{
	char			**argv;
	int				size;
	t_dlist			*tmp;
	int				i;
	t_word			*w;

	size = 1;
	i = 0;
	tmp = dl;
	while (tmp && ((t_lexer_item*)tmp->content)->type == IS_WORD)
	{
		size++;
		tmp = tmp->next;
	}
//	printf("size = %d\n", size);
	argv = (char**)malloc(sizeof(char*) * (size + 1));
	argv[size] = NULL;
	while (i < size && dl)
	{
		w = ((t_lexer_item*)dl->content)->word;
		argv[i] = w->token;
//		printf("argv[ %d ] = %s\n", i, argv[i]);
		dl = dl->next;
		i++;
	}
	return (argv);
}

/*
**	Ouvre un file descriptor pour faire une redirection
*/
int		open_redirection(t_redirection *r, int flags)
{
	int	fd;

	if (r->init == REDICT_IS_FD)
		fd = r->fd;
	else
		fd = open(r->filename->token, flags, 0644);
	return (fd);
}
