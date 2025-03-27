/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:00:32 by joklein           #+#    #+#             */
/*   Updated: 2025/03/27 16:03:59 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*change_input_split(char *input, char *str, char **env_arg_split,
// 		char *input_temp)
// {
// 	int	u;

// 	u = 0;
// 	while (env_arg_split[u])
// 	{
// 		input_temp = ft_strjoin_free(input_temp, env_arg_split[u]);
// 		if (!input_temp)
// 			return (free(input), free(str), NULL);
// 		if (env_arg_split[u + 1] != NULL)
// 		{
// 			input_temp = ft_strjoin_free(input_temp, " ");
// 			if (!input_temp)
// 				return (free(input), free(str), NULL);
// 		}
// 		u++;
// 	}
// 	return (input_temp);
// }

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
	char	*input_temp;

	if (if_heredoc(*i, input))
		*i = skip_heredoc(*i, input);
	else if (if_redir_empty_file(*i, input, copy_env, stream) != 0)
		return (NULL);
	else if (input[*i + 1] == '\0')
		return ((*i)++, input);
	else if (input[*i + 1] == '\"' || input[*i + 1] == '\'')
	{
		input_temp = ft_strndup(input, *i);
		input_temp = ft_strjoin_free(input_temp, &input[(*i) + 1]);
		free(input);
		input = input_temp;
		return (input);
	}
	if (!env_char(input[*i + 1]) && input[*i + 1] != '?')
	{
		(*i)++;
		return (input);
	}
	input = dollar_found(*i, input, copy_env, stream);
	if (!input)
		return (NULL);
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
