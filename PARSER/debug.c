#include <grammar.h>

void	print_debug_item(t_lexer_item *it)
{
	printf("debug item<%p>\n", it);
	if (it)
	{
		if (it->type == IS_REDIRECTION)
			print_redir(it->redir);
		else if (it->type == IS_WORD)
			print_word(it->word);
		else if (it->type == IS_OPERATOR)
			print_word(it->word);
	}
}

void	print_debug_states(t_dlist *s)
{
	t_lexer_item	*it;

//	while (s->next)
//		s = s->next;
	while (s)
	{
		it = (t_lexer_item*)s->content;
		printf("<%p>\n", s);
		if (it->type == IS_REDIRECTION)
			print_redir(it->redir);
		else if (it->type == IS_WORD)
			print_word(it->word);
		else if (it->type == IS_OPERATOR)
			print_word(it->word);
	//	s = s->last;
		s = s->next;
	}
}

void	print_debug_node(t_parser *s)
{
	printf("NODE <%p>\n", s);
	if (s && s->parse_type != -1)
	{
		if (s->parse_type == IS_WORD)
		{
			printf("Is a command\n");
			print_debug_states(s->command);
		}
		else if (s->op)
		{
			printf("Is an operator\n");
			print_debug_item(s->op);
		}
	}
}

void	print_debug_tree(t_parser *s)
{
	if (s && s->parse_type != -1)
	{
		printf("NODE <%p>\n", s);
		print_debug_tree(s->begin);
		if (s->parse_type == IS_WORD)
		{
			printf("Is a command\n");
			print_debug_states(s->command);
		}
		else if (s->op)
		{
			printf("Is an operator\n");
			print_debug_item(s->op);
		}
		print_debug_tree(s->end);
	}
	else
		printf("STOP\n");
}