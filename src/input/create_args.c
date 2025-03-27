/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:59:38 by joklein           #+#    #+#             */
/*   Updated: 2025/03/27 17:13:15 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_arg(char *str, t_list *stream)
{
	int		i;
	int		u;
	char	**args_temp;

	i = 0;
	while (TOKEN->arg[i])
		i++;
	args_temp = malloc((i + 2) * sizeof(char *));
	if (!args_temp)
		return (-1);
	u = 0;
	while (u < i)
	{
		args_temp[u] = TOKEN->arg[u];
		u++;
	}
	args_temp[u] = str;
	args_temp[u + 1] = NULL;
	free(TOKEN->arg);
	TOKEN->arg = args_temp;
	return (0);
}

static int	count_arg_len(char *input, int i, int *q_count)
{
	while (input[i] && !wh_space(input[i]))
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
			while (input[i_temp] != cha)
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

int	creat_args(char *input, int i, t_list *stream, char **copy_env)
{
	int		i_temp;
	int		i_temp2;
	int		quote;
	char	*str;
	char	**args;
	char	*input_temp;

	if (TOKEN->arg == NULL)
	{
		args = malloc(sizeof(char *));
		if (!args)
			return (-1);
		args[0] = NULL;
		TOKEN->arg = args;
	}
	i_temp = i;
	quote = 0;
	i = count_arg_len(input, i, &quote);
	input_temp = ft_strndup(&input[i_temp], i - i_temp);
	input = dollar_handle(input_temp, copy_env, stream);
	if (!input)
		return (-1);
	i_temp = 0;
	while (input[i_temp])
	{
		i_temp2 = i_temp;
		if (!wh_space(input[i_temp]))
		{
			quote = 0;
			i_temp = count_arg_len(input, i_temp, &quote);
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
	i--;
	return (free(input), i);
}
