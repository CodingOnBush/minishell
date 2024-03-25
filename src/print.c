#include "../inc/minishell.h"

void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (!tmp)
		printf("token list empty\n");
	while (tmp)
	{
		printf("%s\t\t%s\t\t%d\n", tmp->str, ft_type_to_str(tmp->type), tmp->attributed);
		tmp = tmp->next;
	}
}
