#include "../inc/minishell.h"

void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (!tmp)
		printf("token list empty\n");
	while (tmp)
	{
		printf("%s\t\t%s\t\t%d\t%d\t%s\n", tmp->str, ft_type_to_str(tmp->type), tmp->attributed, tmp->pos, ft_type_to_str(tmp->err_type));
		tmp = tmp->next;
	}
}

static void	ft_print_arg_list(t_arg *list)
{
	t_arg	*tmp;

	tmp = list;
	if (!tmp)
		printf("arg list empty\n");
	while (tmp)
	{
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

static void	ft_print_infile_list(t_infile *list)
{
	t_infile	*tmp;

	tmp = list;
	if (!tmp)
		printf("infile list empty\n");
	while (tmp)
	{
		printf("%s\t\t%s\n", tmp->filename, tmp->delimiter);
		tmp = tmp->next;
	}
}

static void	ft_print_outfile_list(t_outfile *list)
{
	t_outfile	*tmp;

	tmp = list;
	if (!tmp)
		printf("outfile list empty\n");
	while (tmp)
	{
		printf("%s\t\t%d\n", tmp->filename, tmp->append);
		tmp = tmp->next;
	}
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
		printf("======== TOKEN LIST =======\n");
		ft_print_token_list(tmp->token_list);
		printf("========= ARG LIST ========\n");
		ft_print_arg_list(tmp->arg_list);
		printf("======== INFILE LIST ======\n");
		ft_print_infile_list(tmp->infile_list);
		printf("======= OUTFILE LIST ======\n");
		ft_print_outfile_list(tmp->outfile_list);
		printf("\n");
		tmp = tmp->next;
	}
}
