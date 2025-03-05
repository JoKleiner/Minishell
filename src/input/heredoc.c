/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:51:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/05 11:54:56 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_hd_file(char *str)
{
	int fd;

	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int append_in_file(char *input, char *str)
{
	int fd;

	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
    write(fd, input, ft_strlen(input));
    write(fd, "\n", 1);
	close(fd);
    return(0);
}

int	create_heredoc(char *str, t_list *stream)
{
	char	*input;

	if (create_hd_file(".heredoc") == -1)
		return (-1);
	input = readline("> ");
	if (!input)
		return (free(input), write(1, "exit", 4), -1);
	while (ft_strncmp(input, str, ft_strlen(str)) != 0)
	{
        if(append_in_file(input, ".heredoc") == -1)
            return(free(input), -1);
		free(input);
		input = readline("> ");
		if (!input)
			return (free(input), write(1, "exit", 4), -1);
	}
    TOKEN->in_file = ".heredoc";
    TOKEN->input = 3;
    free(input);
	return (0);
}

int	heredoc(int i, char *input, t_list *stream)
{
	int		u;
	int		i_temp;
	char	*str;

	u = 0;
	i_temp = i;
	while (input[i] && !wh_space(input[i]))
	{
		i++;
		u++;
	}
	str = malloc(u + 1);
	if (!str)
		return (-1);
	u = 0;
	while (i_temp < i)
	{
		str[u] = input[i_temp];
		i_temp++;
        u++;
	}
	str[u] = '\0';
	if (create_heredoc(str, stream) == -1)
		return (-1);
	return (free(str), i);
}
