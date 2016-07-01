#include <spliter.h>
int					IS_A_REDIRECTION(char *cmd) 
{
	return ((ft_isdigit(*cmd) && (*(cmd + 1) == '<' || *(cmd + 1) == '>')) ||
		(*cmd == '<' || *cmd == '>'));
}

char				**lst_to_tab(t_list *lst)
{
	char	**args;
	t_list	*next;
	int		n;

	n = ft_lstsize(lst);
	args = (char**)malloc(sizeof(char*) * (n + 1));
	bzero(args, sizeof(char**) * (n + 1));
	while (lst)
	{
		next = lst->next;
	//	if (*(char*)lst->content)
			args[--n] = (char*)lst->content;
	//	else
	//		n--;
		free(lst);
		lst = next;
	}
	return (args);
}

void				my_pipeline(t_list **ptr, t_list **cmd)
{
	char	**tab;
	t_list	*new;
	t_list	*add;

	add = *ptr;
//	printf("adding pipeline\n");
	tab = lst_to_tab(*cmd);
	new = ft_lstnew_noalloc(tab, sizeof(tab));
	if ((add = *ptr))
	{
		while (add->next)
			add = add->next;
		add->next = new;
	}
	else
		*ptr = new;
	while (*tab)
	{
//		printf("===> |%s|\n", *tab);
		tab++;
	}
	*cmd = NULL;
}

t_command			get_next_command(char *cmd)
{
	char		*str;
	char		*cpy;
	t_list		*tmp;
	t_command	com;

	tmp = NULL;
	memset(&com, 0, sizeof(t_command));
	cpy = ft_strnew(1024);
	str = (char*)cpy;
	*err = 0;
	while (*cmd && !IS_A_REDIRECTION(cmd) && *cmd != ';')
	{
		if (*cmd == '|')
		{
			my_pipeline(&com.pipeline, &tmp);
			cmd++;
		}
		else if (*cmd != ' ')
		{
			printf("cpy %c (%s)\n", *cmd, cpy);
			*(str++) = *(cmd++);
		}
		else
		{
			printf("adding arg: %s\n", cpy);
			while (*cmd == ' ')
				cmd++;
			if (*(str - 1))
				ft_lstadd(&tmp, ft_lstnew_noalloc(cpy, ft_strlen(cpy)));
			cpy = ft_strnew(1024);
			str = (char*)cpy;
		}
	}
	if (tmp)
			my_pipeline(&com.pipeline, &tmp);
	if (IS_A_REDIRECTION(cmd))
	{
		printf("Redirection\n");
		//initialize_redirection(t);
		build_redirection(&com.redirs, &cmd);
	}
	if (cpy == str)
		free(cpy);
	return (com);
}


int more_pipe (int in, int out, t_list cmd)
{
	pid_t	pid;
	char	**tmp;

	tmp = cmd.content;
	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		execvp(tmp[0], tmp);
	}
	return(pid);
}

int ft_pipes (t_list cmds)
{
	t_list	*ptr;
	char	**tmp;
	pid_t	pid;
	int		in;
	int		fd[2];

	in = 0;
	ptr = &cmds;
	if (ptr)
		while (ptr->next)
		{
			pipe (fd);
			more_pipe (in, fd[1], *ptr);
			close (fd[1]);
			in = fd[0];
			ptr = ptr->next;
		}
	if (in != 0)
		dup2 (in, 0);
	tmp = ptr->content;
	return execvp(tmp[0], tmp);
}

void				exec_command(t_command *cmd)
{
	char			**tab;
	t_list			*pipes;
	t_list			*next;

	pipes = cmd->pipeline;
	do_redirections(3, &cmd->redirs);
	ft_pipes(*pipes);
	while (pipes)
	{
		next = pipes->next;
		tab = pipes->content;
		while (*tab)
		{
			printf("%s ", *tab);
			free(*tab);
			tab++;
		}
		free(pipes->content);
		free(pipes);
		pipes = next;
		printf("\n");
	}
	end_redirections(&cmd->redirs);
}

int					main()
{
	t_command	c = get_next_command("/bin/ls -l | /bin/cat -e | /bin/cat -e > out");
	printf("=================\n");
	exec_command(&c);
	return (0);
}
