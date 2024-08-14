#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef enum
{
	NONE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	EXPORT,
	ARG,
	CMD
}	t_token;

typedef struct s_token
{
	char 			**str;
	t_token			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_line;

void	lexer(char **arg, t_line *head);
void	ft_lstadd_back(t_line **head, t_line *new);
void	tokenize_cmd(char *str, t_line *tmp);
void	tokenize(char *arg, t_line *tmp);
void	tokenize_arg(char **arg, int *i, t_line *tmp);
void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c);
t_token	get_token(char *str);

#endif
