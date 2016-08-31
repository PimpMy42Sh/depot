/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:16:42 by fjacquem          #+#    #+#             */
/*   Updated: 2016/08/04 16:04:19 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

/*
**	Execute une/des redirection(s)
**
**	cfg:	0 <=> seul le premier maillon de la liste, sinon toute la liste
**	fd:		file desc. a dupliquer
**	lst:	liste de redirection
*/

static void		do__redirection(int cfg, int fd, t_list *lst)
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

void			do_redirections(int cfg, t_redirections *redirs)
{
	int			i;

	i = 0;
	while (i < MAX_AGR)
	{
		if (redirs->fd_agr1[i] && redirs->fd_agr2[i])
			dup2(redirs->fd_agr2[i], redirs->fd_agr1[i]);
		else if (redirs->close_fd[i])
			close(redirs->fd_agr1[i]);
		i++;
	}
	do__redirection(cfg & CFG_ALL_REDIRECTION_IN, STDIN_FILENO, redirs->in);
	do__redirection(cfg & CFG_ALL_REDIRECTION_OUT, STDOUT_FILENO, redirs->out);
	do__redirection(cfg & CFG_ALL_REDIRECTION_ERR, STDERR_FILENO, redirs->err);
}

/*
**	Pre-initialise une redirection
**
**	fd:		adresse du file desc.
**	type:	adresse du type
**	cmd:	adresse de la ligne de commande
*/

static void		normalize_build_redirection(int *fd, int *type, char **cmd)
{
	if (ft_isdigit(**cmd))
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
	else if (**cmd == '>')
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
	fd = -1;
	normalize_build_redirection(&fd, &type, cmd);
	if (fd >= 0 && fd < MAX_AGR && **cmd == '&')
	{
		(*cmd)++;
		r->fd_agr1[fd] = 1;
		if (**cmd == '-')
			r->close_fd[fd] = 1;
		else
			r->fd_agr2[fd] = **cmd - '0';
		(*cmd)++;
	}
	else if (fd == 2 && type & 1)
	{
		while (**cmd == ' ' || **cmd == '\t' || **cmd == '\n')
			(*cmd)++;
		new_redirection_err(r, type, ft_strword(*cmd));
		while (ft_isalnum(**cmd))
			(*cmd)++;
	}
	else if (type >= 1 && type <= 4)
	{
		while (**cmd == ' ' || **cmd == '\t' || **cmd == '\n')
			(*cmd)++;
		new_redirection(r, type, ft_strword(*cmd));
		while (ft_isalnum(**cmd))
			(*cmd)++;
	}
	return (type);
}
