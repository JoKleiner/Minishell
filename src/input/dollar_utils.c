/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:57:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/15 13:31:51 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_char(char input)
{
	if (input >= 'a' && input <= 'z')
		return (1);
	if (input >= 'A' && input <= 'Z')
		return (1);
	if (input >= '0' && input <= '9')
		return (1);
	if (input == '_')
		return (1);
	return (0);
}


// Returns position of the env in copy_env.
int	find_envp(char *str, char	**copy_env)
{
	int	u;

	u = 0;
	while (copy_env[u])
	{
		if (ft_strncmp(str, copy_env[u], ft_strlen(str)) == 0)
			break ;
		u++;
	}
	return (u);
}

int	if_heredoc(int i, char *input)
{
	if (i >= 2)
	{
		while (i > 2 && input[i] != '<' && !wh_space(input[i]))
			i--;
		while (i > 2 && wh_space(input[i]))
			i--;
		if (input[i - 1] == '<' && input[i - 2] == '<')
			return (1);
	}
	return (0);
}

int	skip_until_char(int i, char *input, char cha)
{
	i++;
	while (input[i] && input[i] != cha)
		i++;
	if (input[i] == '\0')
		i--;
	return (i);
}
