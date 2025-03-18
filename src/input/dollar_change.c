/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/18 12:36:52 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_input(char *input, char *str, char *env_arg, int i)
{
	char	*str_temp;

	str_temp = ft_strndup(input, i);
	if (!str_temp)
		return (free(input), free(str), free(env_arg), NULL);
	str_temp = ft_strjoin_free(str_temp, env_arg);
	if (!str_temp)
		return (free(input), free(str), free(env_arg), NULL);
	str_temp = ft_strjoin_free(str_temp, &input[i + 1 + ft_strlen(str)]);
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

char	*dollar_found(int i, char *input, char **copy_env)
{
	int		i_temp;
	int		u;
	char	*str;
	char	*env_arg;

	i_temp = i;
	env_arg = NULL;
	while (input[i + 1] && env_char(input[i + 1]))
		i++;
	if (i == i_temp)
			return (input);
	str = creat_str(i, i_temp, input);
	if (!str)
		return (free(input), NULL);
	
	u = find_envp(str, copy_env);
	if (copy_env[u])
	{
		env_arg = ft_strdup(&copy_env[u][ft_strlen(str)]);
		if (!env_arg)
			return (free(input), free(str), NULL);
	}
	else
	{
		env_arg = malloc(sizeof(char *));
		env_arg[0] = '\0';
	}
	str[ft_strlen(str) - 1] = '\0';
	input = change_input(input, str, env_arg, i_temp);
	if (!input)
		return (NULL);
	return (input);
}

int	skip_heredoc(int i, char *input)
{
	while (input[i] && !wh_space(input[i]) && !spec_char_wo_dol(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	return (i);
}

char	*dollar_handle(char *input, char **copy_env)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (if_heredoc(i, input))
				i = skip_heredoc(i, input);
			else if (if_redir_empty_file(i, input, copy_env))
				return (NULL);
			else if (env_char(input[i + 1]) || input[i+1] == '?')
			{
				input = dollar_found(i, input, copy_env);
				continue ;
			}
		}
		else if (!input || input[i] == '|')
			return (input);
		else
			i = found_quote(i, &input, copy_env);
		if (i == -1)
			return (NULL);
		i++;
	}
	return (input);
}
