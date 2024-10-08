/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/04 12:56:34 by zelbassa         ###   ########.fr       */
=======
/*   Updated: 2024/10/08 15:18:53 by mel-bouh         ###   ########.fr       */
>>>>>>> f1f72ae (working with a non env)
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse(char *str, t_line **head, char **env, t_parse *data)
{
	char	**arg;
	char	*line;

	if (!checkspaces(str))
		return ;
	if (!checkquotes(str))
		return ;
	line = spacing(str);
<<<<<<< HEAD
	if (!line)
		return ;
	init(data, env);
=======
	data->env = NULL;
	init(&data->env, env);
>>>>>>> f1f72ae (working with a non env)
	line = find_and_replace(line, data->env);
	arg = ft_split(line, ' ');
	if (!arg)
		return ;
	printf("%p and %p\n", data, data->env);
	lexer(arg, head, data);
	triming_quotes(*head);
}
