/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/26 10:52:54 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_quote_less(char *input, int len)
{
	char	*dst;
	int		i;
	int		u;
	char	cha;

	i = 0;
	u = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			cha = input[i];
			i++;
			while (input[i] != cha)
				dst[u++] = input[i++];
			i++;
		}
		else
			dst[u++] = input[i++];
	}
	dst[u] = '\0';
	return (dst);
}

static int	handle_redir(int i, char *input, t_list *stream)
{
	if (input[i] == '>')
		i = redirect_out(input, i, stream);
	else if (input[i] == '<')
		i = redirect_in(input, i, stream);
	return (i);
}

int	input_handle(char *input, t_list *stream, char **copy_env)
{
	int	i;

	input = dollar_handle(input, copy_env, stream);
	if (!input)
		return (TOKEN->error);
	i = 0;
	while (input[i])
	{
		if (wh_space(input[i]))
			(void)0;
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redir(i, input, stream);
		else if (input[i] == '|')
			return (0);
		else
			i = creat_args(input, i, stream);
		if (i == -1)
			return (TOKEN->error);
		i++;
	}
	return (0);
}
