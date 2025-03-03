/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/03 11:08:11 by joklein          ###   ########.fr       */
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
	if (input == '|' || input == '&' || input == ';')
		return (1);
	if (input == '(' || input == ')' || input == '<')
		return (1);
	if (input == '>' || input == '*')
		return (1);
	return (0);
}

int	creat_file(char *input, int i, t_list *stream)
{
	int		num_letter;
	int		i_temp;
	int		u;
	char	*str;
	FILE	*file;

	num_letter = 0;
	i_temp = i;
	while (!wh_space(input[i]) && !wr_symbol(input[i]) && input[i])
	{
		i++;
		num_letter++;
	}
	
	if (wr_symbol(input[i]))
		return (-1);
	str = (char *)malloc(num_letter + 1);
	if (!str)
        return (-1);
	i = i_temp;
	u = 0;
	while (i < i_temp + num_letter)
	{
		str[u] = input[i];
		i++;
		u++;
	}
	str[u] = '\0';
	TOKEN->out_file = str;
	TOKEN->output = 3;
	file = fopen(str, "w");
	if (!file)
	{
		free(str);
		return (-1);
	}
	fclose(file);
	return (i);
}

int	redirect(char *input, int i, t_list *stream)
{
	i++;
	if (input[i] == '>')
	{
		TOKEN->add = 1;
		i++;
	}
	while (wh_space(input[i]))
		i++;
	if (wr_symbol(input[i]))
		return (-1);
	i = creat_file(input, i, stream);
	if (i == -1)
		return (-1);
	return (i);
}

char	**input_handle(char *input, t_list *stream)
{
	int	i;

	// char	**args;
	// char	*token;
	i = 0;
	
	while (input[i])
	{
		
		while (wh_space(input[i]))
			i++;
		
		if (input[i] == '>')
		{
			i = redirect(input, i, stream);
			if (i == -1)
				return (NULL);
		}
		i++;
	}
	// args = malloc(sizeof(char *));
	// i = 0;
	// token = strtok(input, " \t\n");
	// while (token != NULL)
	// {
	// 	args[i++] = token;
	// 	token = strtok(NULL, " \t\n");
	// }
	// args[i] = NULL;
	// return (args);
	return (NULL);
}
