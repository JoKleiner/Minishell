/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:51:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/05 17:32:09 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_hd_file(t_list *stream)
{
	int		fd;
	char	*here_doc;
	int		i;

	if (TOKEN->input != 3)
	{
		i = 1;
		here_doc = ft_strjoin(".heredoc", ft_itoa(i));
		while (!access(here_doc, F_OK))
		{
			i++;
			free(here_doc);
			here_doc = ft_strjoin(".heredoc", ft_itoa(i));
		}
	}
	else
		here_doc = TOKEN->in_file;
	fd = open(here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (here_doc);
}

int	append_in_file(char *input, char *str)
{
	int	fd;

	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

void check_doll()
{
	//
}

int	create_heredoc(char *str, t_list *stream)
{
	char	*input;
	char	*here_doc;

	here_doc = create_hd_file(stream);
	if (!here_doc)
		return (-1);
	input = readline("> ");
	if (!input)
		return (free(input), write(1, "exit", 4), -1);
	while (ft_strncmp(input, str, ft_strlen(str)) != 0)
	{
		if (append_in_file(input, here_doc) == -1)
			return (free(input), -1);
		free(input);
		input = readline("> ");
		if (!input)
			return (free(input), write(1, "exit", 4), -1);
	}
	TOKEN->in_file = here_doc;
	TOKEN->input = 3;
	free(input);
	check_doll();
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
