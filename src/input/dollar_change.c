/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/26 10:30:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*change_input(char *input, char *str, char *env_arg, int i)
{
	char	*input_temp;

	input_temp = ft_strndup(input, i);
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	input_temp = ft_strjoin_free(input_temp, "\"");
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	input_temp = ft_strjoin_free(input_temp, env_arg);
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	input_temp = ft_strjoin_free(input_temp, "\"");
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	input_temp = ft_strjoin_free(input_temp, &input[i + 1 + ft_strlen(str)]);
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	free(input);
	input = input_temp;
	free(str);
	free(env_arg);
	return (input);
}

static char	*dollar_questm(char *input, int i, t_list *stream)
{
	int		num;
	char	*input_temp;
	char	*num_char;

	num = return_value(0, false);
	num_char = ft_itoa(num);
	if (!num_char)
		return (free(input), mem_fail(stream), NULL);
	input_temp = ft_strndup(input, i);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, "\"");
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, num_char);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, "\"");
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, &input[i + 2]);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	free(input);
	return (free(num_char), input_temp);
}

static char	*creat_env_arg(int u, char **copy_env, char *str, t_list *stream)
{
	char	*env_arg;

	if (copy_env[u])
	{
		env_arg = ft_strdup(&copy_env[u][ft_strlen(str)]);
		if (!env_arg)
			return (mem_fail(stream), NULL);
	}
	else
	{
		env_arg = ft_calloc(1, sizeof(char *));
		if (!env_arg)
			return (mem_fail(stream), NULL);
	}
	return (env_arg);
}

static char	*new_input(char *input, char *str, char *env_arg, int i_temp)
{
	if (env_arg[0] == '\0')
		input = change_input_noarg(input, str, env_arg, i_temp);
	else
		input = change_input(input, str, env_arg, i_temp);
	return (input);
}

char	*dollar_found(int i, char *input, char **copy_env, t_list *stream)
{
	int		i_temp;
	int		u;
	char	*str;
	char	*env_arg;

	i_temp = i;
	env_arg = NULL;
	while (input[i + 1] && (env_char(input[i + 1])))
		i++;
	if (input[i_temp + 1] == '?')
		return (dollar_questm(input, i_temp, stream));
	if (i == i_temp)
		return (input);
	str = creat_env_str(i, i_temp, input);
	if (!str)
		return (free(input), mem_fail(stream), NULL);
	u = find_envp(str, copy_env);
	env_arg = creat_env_arg(u, copy_env, str, stream);
	if (!env_arg)
		return (free(str), free(input), NULL);
	str[ft_strlen(str) - 1] = '\0';
	input = new_input(input, str, env_arg, i_temp);
	if (!input)
		mem_fail(stream);
	return (input);
}
