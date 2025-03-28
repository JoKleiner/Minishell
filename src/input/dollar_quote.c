/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:53:40 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 14:07:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_input_noarg(char *input, char *str, char *env_arg, int i)
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

static int	double_quote(int i, char **input, char **copy_env, t_token *stream)
{
	int	i_temp;

	i++;
	while ((*input)[i] && (*input)[i] != '\"')
	{
		if ((*input)[i] == '$')
		{
			i_temp = i;
			while ((*input)[i_temp] != '\"')
				i_temp--;
			if (if_heredoc(i_temp, *input))
			{
				i++;
				continue ;
			}
			*input = dollar_found(i, *input, copy_env, stream);
			if (!(*input))
				return (-1);
		}
		i++;
	}
	return (i);
}

int	found_quote(int i, char **input, char **copy_env, t_token *stream)
{
	if ((*input)[i] == '\'')
		i = skip_until_char(i, *input, '\'');
	else if ((*input)[i] == '\"')
	{
		if ((*input)[i + 2] == '\"')
			return (i + 2);
		i = double_quote(i, input, copy_env, stream);
		if ((*input)[i] == '\0')
			i--;
	}
	return (i);
}
