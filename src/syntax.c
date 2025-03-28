/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:20:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 10:49:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*syncheck_redir(int i, char *input)
{
	char	cha[3];

	cha[2] = '\0';
	cha[1] = '\0';
	if (input[i + 1] == input[i])
		i++;
	if (input[i] == '>' && input[i + 1] == '|')
	{
		if (i > 0 && input[i - 1] == '>')
			i--;
		i++;
	}
	i++;
	while (wh_space(input[i]))
		i++;
	if (input[i] == '\0')
		return (ft_strdup("newline"));
	if (redir_char(input[i]))
	{
		cha[0] = input[i];
		if (input[i] == input[i + 1])
			cha[1] = input[i + 1];
		return (ft_strdup(cha));
	}
	return (NULL);
}

int	pipe_syntax(int i, char *input)
{
	i++;
	while (wh_space(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd("|", STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free(input);
		return (-1);
	}
	return (i);
}

int	redir_syntax(int i, char *input)
{
	char	*syn_str;

	syn_str = NULL;
	syn_str = syncheck_redir(i, input);
	if (syn_str != NULL)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(syn_str, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free(syn_str);
		free(input);
		return (-1);
	}
	return (i);
}

void	first_pipe_syntax(char *input)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd("|", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(input);
}

int	check_syntax(char *input)
{
	int	i;

	i = 0;
	while (wh_space(input[i]))
		i++;
	if (input[i] == '|')
		return (first_pipe_syntax(input), 2);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = skip_until_char(i, input, input[i]);
			if (input[i] == '\0')
				return (free(input), 2);
		}
		else if (input[i] == '>' || input[i] == '<')
			i = redir_syntax(i, input);
		else if (input[i] == '|')
			i = pipe_syntax(i, input);
		if (i == -1)
			return (2);
		i++;
	}
	return (0);
}
