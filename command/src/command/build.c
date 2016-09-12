#include <command.h>

/*
**	Indique si une chaine de caractere est uniquement numerique
**
**	s:	La chaine a verifier
*/

static int		is_a_file_descriptor(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

/*
**	Pre-initialize un agregateur
**
**	r:		adresse de la redirection
**	fd:		file desc. standard
**	type:	type de redirection
**	cmd:	adresse de la ligne de commande
*/

void			build_agregateur(t_redirections *r, int fd,
								int type, char **cmd)
{
	t_agregateur	a;
	char			*word;

	ft_bzero(&a, sizeof(t_agregateur));
	a.fd_1 = (fd == -1) ? type & 1 : fd;
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
		a.fd_2 = open(word, (type & 1) ? O_CREAT | O_RDWR : O_RDONLY, 0644);
		a.filename = word;
	}
	while (**cmd == ' ')
		(*cmd)++;
	(*cmd) += ft_strlen(word) + 1;
	ft_lstadd(&r->agr, ft_lstnew(&a, sizeof(t_agregateur)));
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
	else
	{
		*type = 1 << (**cmd == '<');
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
	else
	{
		if (fd == -1)
			fd = type & 1;
		while (**cmd == ' ')
			(*cmd)++;
		new_redirection(r, fd, type, ft_strword(*cmd));
		while (**cmd != ' ' && **cmd)
			(*cmd)++;
	}
	return (type);
}
