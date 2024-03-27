#include "../inc/minishell.h"

void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	printf("TOKEN LIST\n");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("%s\t\t%s\t\t%d\t%d\t%s\n", tmp->str, ft_type_to_str(tmp->type), tmp->attributed, tmp->pos, ft_type_to_str(tmp->err_type));
		tmp = tmp->next;
	}
}

void	ft_print_arg_list(t_arg *list)
{
	t_arg	*tmp;

	tmp = list;
	printf("ARGLIST\t:");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("[%s]", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

static void	ft_print_infile_list(t_infile *list)
{
	t_infile	*tmp;

	tmp = list;
	printf("INFILE\t:");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("[%s %s]", tmp->filename, tmp->delimiter);
		tmp = tmp->next;
	}
	printf("\n");
}

static void	ft_print_outfile_list(t_outfile *list)
{
	t_outfile	*tmp;

	tmp = list;
	printf("OUTFILE\t:");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("[%s %d]", tmp->filename, tmp->append);
		tmp = tmp->next;
	}
	printf("\n");
}

void	ft_print_cmd_list(t_cmd *list)
{
	t_cmd	*tmp;

	tmp = list;
	if (!tmp)
		printf("cmd list empty\n");
	while (tmp)
	{
		printf("=========== CMD ===========\n");
		ft_print_token_list(tmp->token_list);
		ft_print_arg_list(tmp->arg_list);
		ft_print_infile_list(tmp->infile_list);
		ft_print_outfile_list(tmp->outfile_list);
		printf("===========================\n");
		tmp = tmp->next;
	}
}
