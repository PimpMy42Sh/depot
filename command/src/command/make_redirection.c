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

int				is_a_file_descriptor(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void			build_agregateur(t_redirections *r, int fd, int type, char **cmd)
{
	t_agregateur	a;
	char			*word;

	ft_bzero(&a, sizeof(t_agregateur));
	if (fd == -1)
		a.fd_1 = type & 1;
	else
		a.fd_1 = fd;
	word = ft_strword(*cmd);
	if (!ft_strcmp("-", word))
	{
		a.close = 1;
		free(word);
	}
	else if (is_a_file_descriptor(word))
	{
		a.fd_2 = ft_atoi(word);
		free(word);
	}
	else
	{
		if (type & 1)
			a.fd_2 = open(word, O_CREAT | O_RDONLY, 0644);
		else
			a.fd_2 = open(word, O_RDONLY);
		a.filename = word;
	}
	while (**cmd == ' ')
		(*cmd)++;
	(*cmd) += ft_strlen(word);
	ft_lstadd(&r->agr, ft_lstnew(&a, sizeof(t_agregateur)));
}

void		do__agr_close(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (a->close)
			close(a->fd_1);
		lst = lst->next;
	}	
}

void		do__agr_dup(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (!a->close)
			dup2(a->fd_2, a->fd_1);
		lst = lst->next;
	}
}

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

void			do_redirections(int cfg, t_redirections *redirs, int in, int out)
{
	do__agr_close(redirs->agr);
	do__redirection(cfg & CFG_ALL_REDIRECTION_IN, in, redirs->in);
	do__redirection(cfg & CFG_ALL_REDIRECTION_OUT, out, redirs->out);
	do__redirection(cfg & CFG_ALL_REDIRECTION_ERR, STDERR_FILENO, redirs->err);
	do__agr_dup(redirs->agr);
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
		*fd = ft_atoi(*cmd);
		while (ft_isdigit(**cmd))
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
	if (**cmd == '&')
	{
		(*cmd)++;
		build_agregateur(r, fd, type, cmd);
	}
	else if (fd == 2 && type & 1)
	{
		while (**cmd == ' ')
			(*cmd)++;
		new_redirection_err(r, type, ft_strword(*cmd));
		while (**cmd != ' ' && **cmd)
			(*cmd)++;
	}
	else if (type >= 1 && type <= 4)
	{
		while (**cmd == ' ')
			(*cmd)++;
		new_redirection(r, type, ft_strword(*cmd));
		while (**cmd != ' ' && **cmd != '|' && **cmd != '<' &&
			**cmd != '>' && **cmd != ';' && **cmd)
			(*cmd)++;
	}
	else
		return (0);
	return (type);
}
