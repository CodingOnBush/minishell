#include "../inc/minishell.h"

int	ft_check_quote_error(char *line)
{
	int	single_quote;
	int	double_quotes;

	single_quote = 0;
	double_quotes = 0;
	while (*line != '\0')
	{
		if (*line == SINGLE_QUOTE)
			single_quote++;
		else if (*line == DOUBLE_QUOTES)
			double_quotes++;
		line++;
	}
	if (single_quote % 2 != 0 || double_quotes % 2 != 0)
		return (FAIL);
	return (SUCCESS);
}

int ft_check_double_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (FAIL);
		token = token->next;
	}
	return (SUCCESS);
}
