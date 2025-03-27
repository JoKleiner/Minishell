/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:20:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/27 11:23:25 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_char(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '&')
		return (1);
	return (0);
}

char	*syncheck_redir(int i, char *input)
{
	char	*syn_str;
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
		syn_str = ft_strdup(cha);
		return (syn_str);
	}
	return (NULL);
}

int	check_syntax(char *input)
{
	int		i;
	char	*syn_str;

	i = 0;
	syn_str = NULL;
	while (wh_space(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd("|", STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free(input);
		return (2);
	}
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = skip_until_char(i, input, input[i]);
			if (input[i] == '\0')
				return (free(input), 2);
		}
		if (input[i] == '>' || input[i] == '<')
		{
			syn_str = syncheck_redir(i, input);
			if (syn_str != NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `",
					STDERR_FILENO);
				ft_putstr_fd(syn_str, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				free(syn_str);
				free(input);
				return (2);
			}
		}
		if (input[i] == '|')
		{
			i++;
			while (wh_space(input[i]))
				i++;
			if (input[i] == '|')
			{
				ft_putstr_fd("syntax error near unexpected token `",
					STDERR_FILENO);
				ft_putstr_fd("|", STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				free(input);
				return (2);
			}
		}
		i++;
	}
	return (0);
}

// Syntax check
// >>
// <| abc
// | abc

// if (input[i] == '>')
// {
// 	i++;
// 	while (input[i] && wh_space(input[i]))
// 		i++;
// 	if (input[i] == '>')
// 		syn_char = input[i];
// 	return (syn_char);
// }
// if (input[i])