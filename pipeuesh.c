# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	count;
	unsigned char	*str1;
	unsigned char	*str2;

	count = 0;
	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	while (count < n)
	{
		str1[count] = str2[count];
		count++;
	}
	return (str1);
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*frais;
	void	*tmp;

	tmp = NULL;
	if (content != NULL)
	{
		tmp = (void *)malloc(content_size * sizeof(void *));
		if (content_size > 0)
			tmp = ft_memcpy(tmp, content, content_size);
	}
	frais = (t_list *)malloc(sizeof(t_list));
	if (frais)
	{
		frais->content = tmp;
		if (tmp == NULL)
			frais->content_size = 0;
		else
			frais->content_size = content_size;
		frais->next = NULL;
		return (frais);
	}
	return (NULL);
}

int more_pipe (int in, int out, t_list cmd)
{
	pid_t pid;
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
	t_list *ptr;
	char	**tmp;
	pid_t pid;
	int in;
	int fd[2];

	in = 0;
	ptr = &cmds;
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

int main (void)
{
	t_list	*cmds;
	t_list	*ptr;
	char *ls[] = { "ls", "-lF", "a.out", 0 };
	char *cat[] = { "cat", "-e", 0 };
	int i;

	i = 252; // nombre de chats (limite sur mon mac à 252 // clang test.c ; ./a.out | wc -c)
	cmds = ft_lstnew(ls, sizeof(ls));
	ptr = cmds;
	while (i)
	{
		cmds->next = ft_lstnew(cat, sizeof(cat));
		cmds = cmds->next;
		i--;
	}
	return ft_pipes(*ptr);
}