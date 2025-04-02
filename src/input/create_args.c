/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:59:38 by joklein           #+#    #+#             */
/*   Updated: 2025/04/02 15:39:01 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_arg(char *str, t_token *stream)
{
	int		i;
	int		u;
	char	**args_temp;

	i = 0;
	while (stream->arg[i])
		i++;
	args_temp = malloc((i + 2) * sizeof(char *));
	if (!args_temp)
		return (-1);
	u = 0;
	while (u < i)
	{
		args_temp[u] = stream->arg[u];
		u++;
	}
	args_temp[u] = str;
	args_temp[u + 1] = NULL;
	free(stream->arg);
	stream->arg = args_temp;
	return (0);
}

static int	count_arg_len(char *input, int i, int *q_count)
{
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = skip_until_char(i, input, input[i]);
			(*q_count)++;
		}
		i++;
	}
	return (i);
}

static char	*fill_str(char *str, int i, int i_temp, char *input)
{
	int		u;
	char	cha;

	u = 0;
	while (i_temp < i)
	{
		if (input[i_temp] == '\'' || input[i_temp] == '\"')
		{
			cha = input[i_temp];
			i_temp++;
			while (input[i_temp] && input[i_temp] != cha)
			{
				str[u] = input[i_temp];
				i_temp++;
				u++;
			}
			i_temp++;
			continue ;
		}
		str[u] = input[i_temp];
		u++;
		i_temp++;
	}
	str[u] = '\0';
	return (str);
}

static int	creat_args(t_token *stream, int quote, char *input)
{
	char	*str;
	int		i_temp;
	int		i_temp2;

	i_temp = 0;
	while (input[i_temp])
	{
		i_temp2 = i_temp;
		if (!wh_space(input[i_temp]))
		{
			quote = 0;
			i_temp = count_arg_len2(input, i_temp, &quote);
			str = malloc((i_temp - (quote * 2)) + 1);
			if (!str)
				return (-1);
			str = fill_str(str, i_temp, i_temp2, input);
			if (add_arg(str, stream) == -1)
				return (free(str), -1);
			if (input[i_temp] == '\0')
				i_temp--;
		}
		i_temp++;
	}
	return (0);
}

int	args_handle(char *input, int i, t_token *stream, char **copy_env)
{
	int		i_temp;
	int		quote;
	char	**args;
	char	*input_temp;

	if (stream->arg == NULL)
	{
		args = malloc(sizeof(char *));
		if (!args)
			return (-1);
		args[0] = NULL;
		stream->arg = args;
	}
	i_temp = i;
	quote = 0;
	i = count_arg_len(input, i, &quote);
	input_temp = ft_strndup(&input[i_temp], i - i_temp);
	input = dollar_handle(input_temp, copy_env, stream);
	if (!input)
		return (-1);
	if (creat_args(stream, quote, input) != 0)
		return (-1);
	i--;
	return (free(input), i);
}
