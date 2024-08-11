#include "minishell.h"

int	special_char(char *str, int i)
{
	if (str[i] == '&' || str[i] == ';')
		return (1);
	if (str[i] == '|' && str[i + 1] == '|')
		return (1);
	return (0);
}

int	checkquotes(char *line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(quotes[1] % 2))
			quotes[0]++;
		else if (line[i] == '\"' && !(quotes[0] % 2))
			quotes[1]++;
		else if (special_char(line, i) && !(quotes[0] % 2) && !(quotes[1] % 2))
		{
			write (2, "Parsing error near '", 20);
			write (2, &line[i], 1);
			write (2, "'\n", 2);
			return (0);
		}
		i++;
	}
	if ((quotes[0] % 2) || (quotes [1] % 2))
		return (ft_putstr_fd("Parsing error: missing closing quotation\n", 2),0);
	return (1);
}

int	found(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	tokenize_arg(char **arg, int *i, t_line *tmp, int c)
{
	tmp->str = NULL;
	while (arg[*i] && !found(arg[*i], c))
	{
		tmp->str = ft_strjoin(tmp->str, arg[*i]);
		*i++;
	}
	tmp->type = ARG;
	tmp->next = NULL;
}

t_token	get_token(char *str)
{
	if (!str)
		return (NULL);
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

void	tokenize(char *arg, t_line *tmp)
{
	tmp->str = ft_strdup(arg);
	tmp->type = get_token(arg);
	tmp->next = NULL;
}

int	is_command(char **arg, int i)
{
	if (i == 0 && get_token(arg[i + 1]) == NONE)
		return (1);
}

void	lexer(char **arg, t_line *head)
{
	t_line	*tmp;
	int		i;

	i = 0;
	tmp = head;
	head = malloc(sizeof(t_line));
	if (!head)
		return ;
	while (arg[i])
	{
		if (!ft_strncmp(arg[i], "\"", 1))
			tokenize_arg(arg, &i, tmp, '\"');
		else if (!ft_strncmp(arg[i], "\'", 1))
			tokenize_arg(arg, &i, tmp, '\'');
		else if (get_token(arg[i]) != NONE)
			tokenize(arg[i], tmp);
		else if (is_command(arg, i))
	}
}
t_line	*parse(char *line)
{
	char	**arg;
	t_line	*head;

	if (!checkquotes(line))
		return (NULL);
	head = NULL;
	arg = ft_split(line, ' ');
	if (!arg)
		return (NULL);
	lexer(arg, head);
	return (head);
}

int main(int ac, char **av)
{
	char	*line;
	t_line	*head;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		head = parse(line);
		printf("%s\n", line);
		free(line);
	}
}
