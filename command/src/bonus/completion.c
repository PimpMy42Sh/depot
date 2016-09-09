#include "../../include/minishell.h"
#define NEED_BINAIRY 1
#define NEED_FILENAME 2

t_list		*open_file(char *path, char *file)
{
	t_list			*lst;
	t_list			*new;
	DIR				*d;
	struct dirent	*entry;
	char			*name;

	lst = NULL;
	if ((d = opendir(path)))
	{
		while ((entry = readdir(d)))
		{
			name = entry->d_name;
			if (!ft_strncmp(name, file, ft_strlen(file)) &&
				ft_strcmp("..", name) &&
				ft_strcmp(".", name))
			{
				new = ft_lstnew(NULL, 0);
				new->content = (entry->d_type == DT_DIR) ?
					ft_strjoin(name, "/") :
					ft_strdup(name);
				new->content_size = ft_strlen(name);
				ft_lstadd(&lst, new);
			}
		}
		closedir(d);
	}
	return (lst);
}



void				delete_list(t_list *lst)
{
	t_list			*next;

	while (lst)
	{
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
}

void				print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n",(char*)lst->content);
		lst = lst->next;
	}
}

void				completion(t_it *it, int reset)
{
	char			*path;
	char			*name;
	int				i;
	t_list			*tmp;
	static t_list	*files = NULL;

	i = 0;
	if (reset || !files)
	{
		path = get_path(it, &i);
		name = get_name(it);
		files = open_file(path, name);
		free(path);
		free(name);
	}
	print_list(files);
	if (files)
	{
		ft_strcpy(it->line + i, files->content);
		tmp = files->next;
		free(files->content);
		free(files);
		files = tmp;
	}
}
