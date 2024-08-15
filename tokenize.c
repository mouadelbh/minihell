#include "parsing.h"

int	end_of_quote(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	else
		return (0);
}

static int	count_args(char **arg, int i, char c)
{
	int	count;

	count = 1;
	if (end_of_quote(arg[i], c) && get_token(arg[i + 1]) != NONE)
		return (count);
	i++;
	while (arg[i] && !ft_strchr(arg[i], c))
	{
		count++;
		i++;
	}
	if (arg[i])
		count++;
	return (count);
}

void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c)
{
	int		count;
	int		j;

	count = count_args(arg, *i, c);
	j = 0;
	tmp->str = malloc(sizeof(char *) * (count + 1));
	tmp->str[j] = ft_strdup(arg[*i]);
	j++;
	// printf("token = %i arg = %s\n", get_token(arg[*i]), arg[*i]);
	if (end_of_quote(arg[*i], c) && get_token(arg[*i + 1]) != NONE)
	{
		tmp->str[j] = NULL;
		tmp->type = ARG;
		*i += 1;
		return ;
	}
	*i += 1;
	while (arg[*i] && !ft_strchr(arg[*i], c) && get_token(arg[*i + 1]) != NONE)
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	if (arg[*i])
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	tmp->str[j] = NULL;
	tmp->type = ARG;
	tmp->next = NULL;
}

void	tokenize_arg(char **arg, int *i, t_line *tmp)
{
	int	count;
	int	j;

	count = 0;
	j = *i;
	while (arg[j] && get_token(arg[j]) == NONE)
	{
		count++;
		j += 1;
	}
	j = 0;
	tmp->str = malloc(sizeof(char *) * (count + 1));
	while (arg[*i] && get_token(arg[*i]) == NONE)
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	tmp->str[j] = NULL;
	tmp->type = ARG;
	tmp->next = NULL;
}

void	tokenize(char *arg, t_line *tmp)
{
	tmp->str = malloc(sizeof(char *) * 2);
	tmp->str[0] = ft_strdup(arg);
	tmp->str[1] = NULL;
	tmp->type = get_token(arg);
	tmp->next = NULL;
}

void	tokenize_cmd(char *str, t_line *tmp)
{
	tmp->str = malloc(sizeof(char *) * 2);
	tmp->str[0] = ft_strdup(str);
	tmp->str[1] = NULL;
	tmp->type = CMD;
	tmp->next = NULL;
}
