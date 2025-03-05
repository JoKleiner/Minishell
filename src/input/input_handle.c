/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/04 17:15:11 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

int	wr_symbol(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '$')
		return (1);
	return (0);
}

int	add_arg(char *str, char ***args)
{
	int		i;
	int		u;
	char	**args_temp;

	i = 0;
	if (!str || !args)
		return (1);
	while (*args && (*args)[i])
		i++;
	args_temp = malloc((i + 2) * sizeof(char *));
	if (!args_temp)
		return (free(str), 1);
	u = 0;
	while (u < i)
	{
		args_temp[u] = (*args)[u];
		u++;
	}
	args_temp[u] = str;
	args_temp[u + 1] = NULL;
	free(*args);
	*args = args_temp;
	return (0);
}

int	creat_args(char *input, int i, char ***args)
{
	int		i_temp;
	int		u;
	char	*str;
	int		br_count;

	i_temp = i;
	br_count = 0;
	while (!wh_space(input[i]) && !wr_symbol(input[i]) && input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
			br_count++;
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
			{
				if (input[i] == '$')
				{
					//
				}
				i++;
			}
			br_count++;
		}
		i++;
	}
	if (wr_symbol(input[i]))
	{
		//
	}
	str = malloc((i - i_temp - br_count * 2) + 1);
	if (!str)
		return (-1);
	u = 0;
	while (i_temp < i)
	{
		if (input[i_temp] == '\'')
		{
			i_temp++;
			while (input[i_temp] != '\'')
			{
				str[u] = input[i_temp];
				u++;
				i_temp++;
			}
			i_temp++;
		}
		if (input[i_temp] == '\"')
		{
			i_temp++;
			while (input[i_temp] != '\"')
			{
				if (input[i_temp] == '$')
				{
					//
				}
				str[u] = input[i_temp];
				u++;
				i_temp++;
			}
			i_temp++;
		}
		str[u] = input[i_temp];
		u++;
		i_temp++;
	}
	str[u] = '\0';
	if (add_arg(str, args) == 1)
		return (free(str), -1);
	return (i);
}

t_list	*new_stream(t_list *stream, t_list *stream_one)
{
	if (TOKEN->output == 1)
		TOKEN->output = 2;
	stream = init_stream(stream_one);
	TOKEN->input = 2;
	return (stream);
}

int	handle_redir(int i, char *input, t_list *stream)
{
	while (wh_space(input[i]))
		i++;
	if (input[i] == '>')
	{
		i = redirect_out(input, i, stream);
	}
	else if (input[i] == '<')
	{
		i = redirect_in(input, i, stream);
	}
	return (i);
}

int	pipe_doll(int i, char *input, t_list *stream_one, char ***args)
{
	t_list	*stream;
	char	**args_temp;

	args_temp = NULL;
	stream = ft_lstlast(stream_one);
	if (input[i] == '|')
	{
		TOKEN->arg = *args;
		TOKEN->cmd = *args[0];
		stream = new_stream(stream, stream_one);
		*args = args_temp;
		i++;
	}
	else if (input[i] == '$')
	{
		//
	}
	return (i);
}

int	input_handle(char *input, t_list *stream_one)
{
	int		i;
	t_list	*stream;
	char	**args;

	i = 0;
	stream = stream_one;
	args = NULL;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			i = handle_redir(i, input, stream);
		else if (input[i] == '|' || input[i] == '$')
		{
			i = pipe_doll(i, input, stream_one, &args);
			stream = ft_lstlast(stream_one);
		}
		else if (input[i])
			i = creat_args(input, i, &args);
		if (i == -1)
			return (1);
		i++;
	}
	if (args)
	{
		TOKEN->arg = args;
		TOKEN->cmd = args[0];
	}
	return (0);
}
