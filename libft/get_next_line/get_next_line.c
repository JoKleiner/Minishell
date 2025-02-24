/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:40 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:24:17 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*init_temp(char *temp, char **line, char **buffer)
{
	int	i;

	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	*line = ft_strndup(temp, i + 1);
	if (*line == NULL)
		return (free_str(buffer), NULL);
	if (temp[i] == '\n')
	{
		temp = ft_memcpy(temp, &temp[i + 1], ft_strlen(temp) - i);
		return (free_str(buffer), *line);
	}
	if (temp[0] == '\0')
		return (free_str(line), free_str(buffer), NULL);
	return (*line);
}

char	*expand_line(char **line, char *buffer, int i)
{
	char	*temp2;
	char	*line2;

	temp2 = ft_strndup(buffer, i + 1);
	if (temp2 == NULL)
		return (NULL);
	line2 = ft_strjoin(*line, temp2);
	if (line2 == NULL)
		return (free(temp2), NULL);
	free(temp2);
	free(*line);
	*line = line2;
	return (*line);
}

int	get_next_line_2(char **line, char *temp, char *buffer, int bytes_num)
{
	int	i;
	int	u;

	i = 0;
	buffer[bytes_num] = '\0';
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	u = i;
	if (buffer[i] == '\n')
		u++;
	if (*line == NULL)
	{
		*line = ft_strndup(buffer, u);
		if (*line == NULL)
			return (-1);
	}
	else if (expand_line(line, buffer, i) == NULL)
		return (-1);
	temp = ft_memcpy(temp, &buffer[i + 1], bytes_num - i);
	temp[bytes_num - i] = '\0';
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	temp[BUFFER_SIZE + 1];
	int			num;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	line = NULL;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL || (temp[0] && init_temp(temp, &line, &buf) == NULL))
		return (NULL);
	if (buf == NULL)
		return (line);
	while (1)
	{
		num = read(fd, buf, BUFFER_SIZE);
		if ((num < 0) || (num == 0 && !line && !temp[0]))
			return (free_str(&line), free_str(&buf), temp[0] = '\0', NULL);
		num = get_next_line_2(&line, temp, buf, num);
		if (num == -1)
			return (free_str(&line), free_str(&buf), NULL);
		if (num != BUFFER_SIZE)
			break ;
	}
	return (free_str(&buf), line);
}
