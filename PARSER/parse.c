#include <grammar.h>
#include "../REDIRECTIONS/adapt/adaptation.h"

void	delete_tree(t_parser **p)
{
	if (*p)
	{
		delete_tree(&(*p)->begin);
		delete_tree(&(*p)->end);
		free(*p);
		*p = NULL;
	}
}
/*
static	t_dlist	*rewind_words(t_dlist **states)
{
	t_dlist 		*dl;
	t_lexer_item	*it;

	dl = *states;
	if (dl)
	{
			(*states) = (*states)->next;
		while (dl)
		{
			it = (t_lexer_item*)dl->content;
			print_debug_item(it);
			if (it->type != IS_WORD)
			{
				dl = dl->next;
				break;
			}
			dl = dl->last;
		}
		return (dl);
	}
	return (NULL);
}*/

t_parser	*create_tree(t_dlist *states, t_parser **ptr)
{
/*	t_parser		*new_node;
	t_parser		*last_node;
	t_lexer_item	*item;
	int				type;

	new_node = NULL;
	if (states)
	{
		last_node = *ptr;
		//if (! verifier la grammaire (verifier la coordonance entre
		//<states -> content> et <states -> next -> content>))
		//	printf("Syntax error");
		//	free_parser
		//	return (NULL);
		new_node = (t_parser*)malloc(sizeof(t_parser));
		item = (t_lexer_item*)states->content;
		type = item->type;
		new_node->logical_value = 0;
		new_node->parse_type = type;
		if (type == IS_WORD)
		{
			printf("WORD_LIST\n");
			new_node->command = states;
			print_debug_item(item);
			new_node->begin = NULL;
			new_node->end = NULL;
			if (!last_node)
			{
				last_node = new_node;
				*ptr = new_node;
			}
			last_node->begin = new_node;
			last_node->end = create_tree(states->next, &last_node);
			return (new_node);
		}
		else if (type == IS_REDIRECTION || type == IS_OPERATOR)
		{
			//verifier grammaire
			if (!last_node)
			{
				write(2, "Syntax Error\n", 13);
				return (NULL);
			}
			printf("NEW_OPERANDE\n");
			//print_debug_item(item);

			new_node->begin = last_node;
			last_node->begin = NULL;
			new_node->op = item;
			printf("BEGIN IS\n");
			print_debug_node(new_node->begin);
			printf("====>\n");
			new_node->end = create_tree(states->next, &new_node);
			printf("END\n");
			print_debug_node(new_node->end);
			printf("======>\n");
		}
		else
			write(2, "Bad parsing\n", 12);
		return (new_node);
	}
	return (*ptr);
	printf("STOP\n");
*/
	return (NULL);
	(void)states;
	(void)ptr;
}


t_dlist	*get_next_op(t_dlist *lst)
{
	while (lst)
	{
		if (((t_lexer_item*)lst->content)->type != IS_WORD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}


/*
**	Do_redirection (non multi redirection)
**
**	Execute une seule de redirection
*/
int			do_redirection(t_term *t, t_redirection *r, t_dlist *states)
{
	pid_t			child;
	char			*path1;
	char			*path2;
	int				type;

	path1 = NULL;
	if (!(child = fork()))
	{
		path2 = ((t_lexer_item*)states->next->content)->word->token;
		if ((type = r->type) == REDICT_LESS)
		{
			printf("Simple chevron droit\n");
			chevron_droite_filename(t, path1, get_last_argv(states),
					path2);
		}
		else if (type == REDICT_LLESS)
		{
			printf("Double chevron droit\n");
			double_chevron_droite_filename(t, path1, get_last_argv(states),
			path2);
		}
		else if (type == REDICT_PIPE)
		{
			printf("PIPE\n");
			run_pipe(t, path1, path2, states);
		}
		else
			write(2, "Unknown redirection\n", 19);
	}
	wait(NULL);
	return (0);
}

/*
**	Execution
*/
int		exec_simple_command(t_term *t, t_dlist *lst, t_lexer_item *it)
{
	pid_t			child;
	char			**args;

	//child = fork();
	child = 0;
	args = NULL;
	if (!child)
	{
		if (it->type == IS_WORD)
		{
			args = get_last_argv(lst->last);
			printf("%s\n", args[0]);
			execve(args[0], args, t->env);
		}
	}
	else
		write(2, "fork fails\n", 11);
	wait(NULL);
	free(args);
	return (0);
}
void	do_parsing(t_term *t, t_dlist *plst)
{
	t_lexer_item	*it;
	t_dlist			*lst;
	int				type;

	lst = plst;
	type = -2;
	while ((lst = get_next_op(lst)))
	{
		it = (t_lexer_item*)lst->content;
		type = it->type;
		if (type == IS_REDIRECTION)
		{
			//Verifier la grammaire (item  / item->next)
			//	Selon la configuation de le grammmaire
			do_redirection(t, it->redir, lst);

		}
		else if (type == IS_OPERATOR)
		{
			printf("OPERATOR\n");
			//Operator
			//vu qu'il n'y a que le ';', on fait rien
			exec_simple_command(t, lst, it);
		}
		lst = lst->next;
	}
	if (type == -2 && plst)
	{
		exec_simple_command(t, plst, plst->content);
	}
}

int		parse (t_term *t, const char *cmd)
{
	t_dlist		*states;
	t_parser	*tree;

//	Verifier(ligne_de_commande&(*p));
	tree = NULL;
	states = create_states(cmd);
	print_debug_states(states);
	if (states)
	{
		printf("================= PARSING =================\n");
		do_parsing(t, states);
		printf("================= PARSING =================\n");
		//print_debug_tree(tree);
		//delete_tree(&tree);
		ft_dlstfree(&states, &free_item);
	}
	return (0);
	(void)tree;
}

void	free_item(t_lexer_item *it)
{
//	printf("free item<%p>\n", it);
	if (it->type == IS_REDIRECTION)
		free(it->redir);
	else if (it->type == IS_WORD)
	{
		free(it->word->token);
		free(it->word);
	}
	else if (it->type == IS_OPERATOR)
	{
		free(it->word->token);
		free(it->word);
	}
	free(it);
}
