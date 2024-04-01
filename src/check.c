#include "../inc/minishell.h"

int	ft_check_quote_error(char *line)
{
	int	single_quote;
	int	double_quotes;

	single_quote = 0;
	double_quotes = 0;
	while (*line)
	{
		if (*line == '\'' && ft_strchr(line + 1, '\'') != NULL)
			line += ft_strchr(line + 1, '\'') - line + 1;
		else if (*line == '\"' && ft_strchr(line + 1, '\"') != NULL)
			line += ft_strchr(line + 1, '\"') - line + 1;
		else
		{
			if (*line == '\"')
				double_quotes++;
			if (*line == '\'')
				single_quote++;
			line++;
		}
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
