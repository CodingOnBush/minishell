#include "../inc/minishell.h"

int	ft_check_quote_error(char *line)
{
	int	single_quote;
	int	double_quotes;
	int	i;

	single_quote = 0;
	double_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && ft_strchr(line + i + 1, '\'') != NULL)
			i += ft_strchr(line + i + 1, '\'') - line + 1;
		else if (line[i] == '\"' && ft_strchr(line + i + 1, '\"') != NULL)
			i += ft_strchr(line + i + 1, '\"') - line + 1;
		else
		{
			if (line[i] == '\"')
				double_quotes++;
			if (line[i] == '\'')
				single_quote++;
			i++;
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
