/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/07 09:56:28 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	spez_char(char input)
{
	if (input >= 'a' || input <= 'z')
		return (0);
	if (input >= 'A' || input <= 'Z')
		return (0);
	if (input >= '0' || input <= '9')
		return (0);
	if (input == '_')
		return (0);
	return (1);
}

int	find_envp(char *str, t_list *stream)
{
	int	u;

	u = 0;
	stream = NULL;
	while (environ[u])
	{
		if (ft_strncmp(str, environ[u], ft_strlen(str)) == 0)
			break ;
		u++;
	}
	return (u);
}

char *change_input(char *input, char *str, char *env_arg)
{
	int pos;
	
	(void)env_arg;
	pos = ft_strstr_num(input, str);
	printf("%d", pos);
	return(str);
}

char	*dollar_found(int i, char *input, t_list *stream)
{
	int		i_temp;
	int		u;
	char	*str;
	char	*env_arg;

	u = 0;
	i_temp = i;
	while (!wh_space(input[i]) && !spez_char(input[i]) && input[i])
	{
		i++;
		u++;
	}
	str = ft_strndup(&input[i_temp + 1], u);
	u = find_envp(str, stream);
	if (environ[u] && i != i_temp + 1
		&& environ[u][ft_strlen(str)] == '=')
	{
		env_arg = ft_strdup(&environ[u][ft_strlen(str) + 1]);
		input = change_input(input, str, env_arg);
	}
	else
	{}
		//input = kill_str_input(input, str);
	return (input);
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

int	skip_single_quote(int i, char *input)
{
	i++;
	while (input[i] != '\'')
		i++;
	i++;
	return (i);
}

char	*dollar_handle(char *input, t_list *stream)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] != '$' && input[i] != '\'' && input[i])
			i++;
		if (input[i] == '$')
		{
			if (if_heredoc(i, input))
				while (!wh_space(input[i]) && input[i])
				{
					i++;
					continue ;
				}
			input = dollar_found(i, input, stream);
		}
		if (input[i] == '\'')
			i = skip_single_quote(i, input);
	}
	return (input);
}
