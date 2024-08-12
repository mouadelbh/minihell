#include "minishell.h"

t_token	get_token(char *str)
{
	if (!str)
		return (NONE);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIR_OUT);
	else if (!ft_strncmp(str, ">>", 1))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 1))
		return (HEREDOC);
	else
		return (NONE);
}

int	is_command(char **arg, int i)
{
	if (i == 0)
		return (1);
	else if (get_token(arg[i - 1]) == PIPE)
		return (1);
	else
		return (0);
}

void	tokenize(char *arg, t_line *tmp)
{
	tmp->str = ft_strdup(arg);
	tmp->type = get_token(arg);
	tmp->next = NULL;
}

void	tokenize_cmd(char *str, t_line *tmp)
{
	tmp->str = ft_strdup(str);
	tmp->type = CMD;
	tmp->next = NULL;
}

void	tokenize_quotarg(char **arg, int *i, t_line *tmp, int c)
{
	int j = *i;
	tmp->str = ft_strdup("");
	while (arg[j] && ft_strchr(arg[j], c))
	{
		printf("arg: %s\n", arg[j]);
		tmp->str = ft_strjoin(tmp->str, arg[j]);
		printf("tmp->str: %s\n", arg[j]);
		j += 1;
	}
	*i = j;
	tmp->type = ARG;
	tmp->next = NULL;
}

void	tokenize_arg(char **arg, int *i, t_line *tmp)
{
	tmp->str = ft_strdup("");
	while (arg[*i] && get_token(arg[*i]) == NONE)
	{
		printf("arg: %s\n", arg[*i]);
		tmp->str = ft_strjoin(tmp->str, arg[*i]);
		printf("tmp->str: %s\n", arg[*i]);
		*i += 1;
	}
	tmp->type = ARG;
	tmp->next = NULL;
}

void	lexer(char **arg, t_line *head)
{
	t_line	*tmp;
	int		i;

	i = 0;
	while (arg[i])
	{
		tmp = malloc(sizeof(t_line));
		if (!tmp)
			return ;
		if (!ft_strncmp(arg[i], "\"", 1))
			tokenize_quotarg(arg, &i, tmp, '\"');
		else if (!ft_strncmp(arg[i], "\'", 1))
			tokenize_quotarg(arg, &i, tmp, '\'');
		else if (get_token(arg[i]) != NONE)
			tokenize(arg[i], tmp);
		else if (is_command(arg, i))
			tokenize_cmd(arg[i], tmp);
		else
			tokenize_arg(arg, &i, tmp);
		ft_lstadd_back(&head, tmp);
		i++;
	}
	while (head)
	{
		printf("str: %s\n", head->str);
		printf("type: %d\n", head->type);
		head = head->next;
	}
}
