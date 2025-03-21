/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/21 15:03:58 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mem_fail(t_list *stream)
{
	ft_errmal("malloc failed");
	TOKEN->error = ENOMEM;
}

char	*change_input(char *input, char *str, char *env_arg, int i)
{
	char	*input_temp;

	input_temp = ft_strndup(input, i);
	if (!input_temp)
		return (free(input), free(str), free(env_arg), NULL);
	input_temp = ft_strjoin_free(input_temp, env_arg);
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

char	*dollar_questm(char *input, int i, t_list *stream)
{
	int		num;
	char	*input_temp;
	char	*num_char;

	num = return_value(0);
	num_char = ft_itoa(num);
	if (!num_char)
		return (free(input), mem_fail(stream), NULL);
	input_temp = ft_strndup(input, i);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, num_char);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	input_temp = ft_strjoin_free(input_temp, &input[i + 2]);
	if (!input_temp)
		return (free(input), free(num_char), mem_fail(stream), NULL);
	free(input);
	free(num_char);
	input = input_temp;
	return (input);
}

char	*creat_env_arg(int u, char **copy_env, char *str, t_list *stream)
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
	str = creat_str(i, i_temp, input);
	if (!str)
		return (free(input), mem_fail(stream), NULL);
	u = find_envp(str, copy_env);
	env_arg = creat_env_arg(u, copy_env, str, stream);
	if (!env_arg)
		return (free(str), free(input), NULL);
	str[ft_strlen(str) - 1] = '\0';
	input = change_input(input, str, env_arg, i_temp);
	if (!input)
		mem_fail(stream);
	return (input);
}

int	skip_heredoc(int i, char *input)
{
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	return (i);
}

static char	*dollar_sign(int *i, char *input, char **copy_env, t_list *stream)
{
	char *input_temp;
	
	
	if (if_heredoc(*i, input))
		*i = skip_heredoc(*i, input);
	else if (if_redir_empty_file(*i, input, copy_env, stream) != 0)
		return (NULL);
	else if (env_char(input[*i + 1]) || input[*i + 1] == '?')
	{
		input = dollar_found(*i, input, copy_env, stream);
		if (!input)
			return (NULL);
		return (input);
	}
	input_temp = ft_strndup(input, *i);
	input_temp = ft_strjoin_free(input_temp, &input[(*i)+1]);
	free(input);
	input = input_temp;
	return (input);
}

char	*dollar_handle(char *input, char **copy_env, t_list *stream)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			input = dollar_sign(&i, input, copy_env, stream);
			if (!input)
				return (NULL);
			continue ;
		}
		else if (input[i] == '|')
			return (input);
		else
			i = found_quote(i, &input, copy_env, stream);
		if (i == -1)
			return (NULL);
		i++;
	}
	return (input);
}
