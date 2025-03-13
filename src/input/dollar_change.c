/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 10:35:02 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_input(char *input, char *str, char *env_arg)
{
	int		pos;
	char	*str_temp;

	pos = ft_strstr_num(input, str);
	str_temp = ft_strndup(input, pos - 1);
	if (!str_temp)
		return (free(input), free(str), free(env_arg), NULL);
	str_temp = ft_strjoin_free(str_temp, env_arg);
	if (!str_temp)
		return (free(input), free(str), free(env_arg), NULL);
	str_temp = ft_strjoin_free(str_temp, &input[pos + ft_strlen(str)]);
	if (!str_temp)
		return (free(input), free(str), free(env_arg), NULL);
	free(input);
	input = str_temp;
	free(str);
	free(env_arg);
	return (input);
}

char	*creat_str(int i, int i_temp, char *input)
{
	char	*str;

	str = ft_strndup(&input[i_temp + 1], i - i_temp);
	if (!str)
		return (NULL);
	str = ft_strjoin_free(str, "=");
	if (!str)
		return (NULL);
	return (str);
}

char	*dollar_found(int i, char *input)
{
	int		i_temp;
	int		u;
	char	*str;
	char	*env_arg;

	i_temp = i;
	env_arg = NULL;
	while (input[i + 1] && env_char(input[i + 1]))
		i++;
	str = creat_str(i, i_temp, input);
	if (!str)
		return (free(input), NULL);
	u = find_envp(str);
	if (environ[u])
	{
		env_arg = ft_strdup(&environ[u][ft_strlen(str)]);
		if (!env_arg)
			return (free(input), free(str), NULL);
	}
	str[ft_strlen(str) - 1] = '\0';
	input = change_input(input, str, env_arg);
	if (!input)
		return (NULL);
	return (input);
}

int	skip_heredoc(int i, char *input)
{
	while (input[i] && !wh_space(input[i]) && !spec_char_wo_dol(input[i]))
	{
		if (input[i] == '\'')
			i = skip_until_char(i, input, '\'');
		if (input[i] == '\"')
			i = skip_until_char(i, input, '\"');
		i++;
	}
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
				i = skip_heredoc(i, input);
			else if (env_char(input[i + 1]))
			{
				input = dollar_found(i, input);
				if (!input)
					return (NULL);
			}
			else
				i++;
			continue ;
		}
		i = found_quote(i, input);
		if (i == -1)
			return (NULL);
		i++;
	}
	return (input);
}
