/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:59:38 by joklein           #+#    #+#             */
/*   Updated: 2025/03/24 11:48:36 by joklein          ###   ########.fr       */
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
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'')
		{
			i = skip_until_char(i, input, '\'');
			(*q_count)++;
		}
		if (input[i] == '\"')
		{
			i = skip_until_char(i, input, '\"');
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

int	creat_args(char *input, int i, t_list *stream)
{
	int		i_temp;
	int		u;
	char	*str;
	char	**args;

	if (TOKEN->arg == NULL)
	{
		args = malloc(sizeof(char *));
		if (!args)
			return (-1);
		args[0] = NULL;
		TOKEN->arg = args;
	}
	i_temp = i;
	u = 0;
	i = count_arg_len(input, i, &u);
	str = malloc((i - i_temp - (u * 2)) + 1);
	if (!str)
		return (-1);
	str = fill_str(str, i, i_temp, input);
	if (add_arg(str, stream) == -1)
		return (free(str), -1);
	if (!wh_space(input[i]))
		i--;
	return (i);
}
