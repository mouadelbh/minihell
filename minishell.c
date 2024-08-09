#include "minishell.h"

void	parse(char *line)
{
	char	**args;
	int		i;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	i = 0;
	
}

int main(int ac, char **av)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		parse(line);
		printf("%s\n", line);
		free(line);
	}
}
