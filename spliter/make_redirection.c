/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:16:42 by fjacquem          #+#    #+#             */
/*   Updated: 2015/11/24 10:16:44 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <spliter.h>

/*
**	Execute les agregateurs de file desc.
**
**	fd:		file desc. a dupliquer
**	mask:	mot binaire (bit a 1 signifie un fd a dupliquer)
*/
static inline void		do__agregateur(int fd, int mask)
{
	int	index;

	index = 0;
	while (mask >> index)
	{
		if ((mask >> index) & 1)
		{
			dup2(index, fd);
			close(index);
		}
	}
}

/*
**	Execute une/des redirection(s)
**
**	cfg:	0 <=> seul le premier maillon de la liste, sinon toute la liste
**	fd:		file desc. a dupliquer
**	lst:	liste de redirection
*/
static inline void		do__redirection(int cfg, int fd, t_list *lst)
{
	t_redirection	*r;

	if (cfg)
	{
		while (lst)
		{
			r = (t_redirection*)lst->content;
			dup2(r->fd, fd);
			close(r->fd);
			lst = lst->next;
		}
	}
	else if (lst)
	{
		r = (t_redirection*)lst->content;
		dup2(r->fd, fd);
		close(r->fd);
	}
}

/*
**	Execute les redirections requises
**
**	cfg:			mask binaire (CFG_ALL_REDIRECTION_IN/OUT)
**	redirections:	donnees de redirections
*/
void					do_redirections(int cfg, t_redirections *redirs)
{
	t_list			*lst;
	t_redirection	*r;
	int				i;

	lst = redirs->in;
	i = 0;
	do__redirection(cfg & CFG_ALL_REDIRECTION_IN, STDIN_FILENO, redirs->in);
	do__agregateur(STDIN_FILENO, redirs->fd_in);
	do__redirection(cfg & CFG_ALL_REDIRECTION_OUT, STDOUT_FILENO, redirs->out);
	do__agregateur(STDOUT_FILENO, redirs->fd_out);
}


/*
**	Pre-initialise une redirection
**
**	fd:		adresse du file desc.
**	type:	adresse du type
**	cmd:	adresse de la ligne de commande
*/
static inline void	normalize_build_redirection(int *fd, int *type, char **cmd)
{
	if (ft_isalpha(**cmd))
	{
		*fd = **cmd - '0';
		(*cmd)++;
	}
	if (!ft_strncmp(*cmd, "<<", 2))
	{
		*type = DCHEVRON_GAUCHE;
		(*cmd) += 2;
	}
	else if (!ft_strncmp(*cmd, ">>", 2))
	{
		*type = DCHEVRON_DROIT;
		(*cmd) += 2;
	}
	else if (**cmd == '<')
	{
		*type = CHEVRON_GAUCHE;
		(*cmd)++;
	}
	else
	{
		*type = CHEVRON_DROIT;
		(*cmd)++;
	}
}

/*
**	Creer une redirection si necessaire
**	Si tel est le cas, un nombre positif est renvoyer sinon 0
**
**	r:		adresse ou enregistrer la redirection
**	cmd:	adresse de la ligne de commande
*/
int				build_redirection(t_redirections *r, char **cmd)
{
	int				fd;
	int				type;

	type = 0;
	if ((ft_isdigit(**cmd) && (*((*cmd) + 1) == '<' || *((*cmd) + 1) == '>')) ||
		(**cmd == '<' || **cmd == '>'))
	{
		normalize_build_redirection(&fd, &type, cmd);
		if (**cmd == '&')
		{
			printf("AGre\n");
			if (type & 1)
				use_agregator_redirection(r, fd, *((*cmd) + 1) - '0');
			else
				use_agregator_redirection(r, *((*cmd) + 1) - '0', fd);
			cmd++;
		}
		while (**cmd == ' ' || **cmd == '\t' || **cmd == '\n')
			(*cmd)++;
		new_redirection(r, type, ft_strword(*cmd));
		while (ft_isalnum(**cmd))
			(*cmd)++;
	}
	return (type);
}
