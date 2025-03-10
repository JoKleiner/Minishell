/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/10 14:29:58 by joklein          ###   ########.fr       */
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

int	find_envp(char *str)
{
	int	u;

	u = 0;
	while (environ[u])
	{
		if (ft_strncmp(str, environ[u], ft_strlen(str)) == 0)
			break ;
		u++;
	}
	return (u);
}

char	*change_input(char *input, char *str, char *env_arg)
{
	int		pos;
	char	*str_temp;

	pos = ft_strstr_num(input, str);
	str_temp = ft_strndup(input, pos-1);
	str_temp = ft_strjoin_free(str_temp, env_arg);
	str_temp = ft_strjoin_free(str_temp, &input[pos + ft_strlen(str)]);
	free(input);
	input = str_temp;
	return (input);
}

char	*dollar_found(int i, char *input)
{
	int		i_temp;
	int		u;
	char	*str;
	char	*env_arg;

	u = 0;
	i_temp = i;
	env_arg = NULL;
	while (input[i + 1] && env_char(input[i + 1]) && !wh_space(input[i + 1]))
	{
		i++;
		u++;
	}
	str = ft_strndup(&input[i_temp+1], u);
	str = ft_strjoin_free(str, "=");
	u = find_envp(str);
	if (environ[u])
		env_arg = ft_strdup(&environ[u][ft_strlen(str)]);
	str[ft_strlen(str) - 1] = '\0';
	input = change_input(input, str, env_arg);
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

int	doppel_quote(int i, char **input)
{
	int i_temp;
	
	i++;
	while ((*input)[i] && (*input)[i] != '$' && (*input)[i] != '\"')
		i++;
	i_temp = i;
	if ((*input)[i] == '$')
	{
		while ((*input)[i_temp] && (*input)[i_temp] != '\"')
			i_temp--;
		if (if_heredoc(i_temp, *input))
			while ((*input)[i] && !wh_space((*input)[i]))
			{
				i++;
				continue ;
			}
		*input = dollar_found(i, *input);
		i++;
	}
	if ((*input)[i] == '\"')
		i++;
	return (i);
}

char	*dollar_handle(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (if_heredoc(i, input))
			{
				while (input[i] && !wh_space(input[i]))
					i++;
				continue ;
			}
			if (env_char(input[i + 1]))
			{
				input = dollar_found(i, input);
				continue ;
			}
		}
		if (input[i] == '\'')
			i = skip_single_quote(i, input);
		if (input[i] == '\"')
			i = doppel_quote(i, &input);
		i++;
	}
	ft_printf("%s\n", input);
	return (input);
}
