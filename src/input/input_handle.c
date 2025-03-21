/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/21 11:25:29 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redir(int i, char *input, t_list *stream, char **copy_env)
{
	if (input[i] == '>')
		i = redirect_out(input, i, stream);
	else if (input[i] == '<')
		i = redirect_in(input, i, stream, copy_env);
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
			i = handle_redir(i, input, stream, copy_env);
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
