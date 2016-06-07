#include <btree.h>
#include <dirent.h>

int					init_lexicaltree_tab(t_btree **root, char **tab, int sentive_case)
{
	int	(*fct)();

	if (!sentive_case)
		fct = &strcasecmp;
	else
		fct = &strcmp;
	while (*tab)
	{
		ft_btreeadd(root, ft_btreenew_noalloc(*tab, ft_strlen(*tab)), fct);
		tab++;
	}
	return (0);
}

int					init_lexicaltree_directory(t_btree **root, char *path, int sentive_case)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*filename;
	int				(*fct)();

	if (!sentive_case)
		fct = &strcasecmp;
	else
		fct = &strcmp;
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)))
		{
			ft_btreeadd(root, ft_btreenew(entry->d_name, ft_strlen(entry->d_name)), fct);
		}
		closedir(dir);
	}
	else
		return (-1);
	return (0);
}

void				ft_btreeprint(t_btree *r)
{
	if (r)
	{
		printf("%s\n", r->content);
		ft_btreeprint(r->left);
		ft_btreeprint(r->right);
	}
}

int					main(void)
{
	char	*path = "/";
	char	*str = ".";
	int		sentive_case = 0;

	t_btree	*root = NULL;
	t_btree	*compare_data = NULL;
	t_list	*result = NULL;

	init_lexicaltree_directory(&root, path, sentive_case);
	//ft_btreeprint(root);
	compare_data = ft_btreenew_noalloc(str, ft_strlen(str));
	ft_btreecmp_all(&result, root, compare_data, (sentive_case ? &strncasecmp : &ft_strncmp));
	printf("================ RESULT ================\n");
	while (result)
	{	
		printf("%s\n", (char*)result->content);
		result = result->next;
	}
	return (0);
}