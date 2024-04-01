#include "../inc/minishell.h"

void	ft_detect_delimiter(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (token->type == HERE_DOC && token->next && token->next->type == WORD)
			token->next->type = LIM;
		token = token->next;
	}
}

void	ft_remove_null_token(t_data *data)
{
	t_token	*token;
	t_token	*prev;

	token = data->token_list;
	prev = NULL;
	while (token)
	{
		if (token->type == WORD && !token->str)
		{
			if (prev)
				prev->next = token->next;
			else
				data->token_list = token->next;
			free(token);
			token = prev;
		}
		prev = token;
		token = token->next;
	}
}
