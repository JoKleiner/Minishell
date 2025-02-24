/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:22 by joklein           #+#    #+#             */
/*   Updated: 2025/01/29 15:06:18 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	count_word(char const *str, char cha)
{
	size_t	wordnum;
	size_t	i;

	i = 0;
	wordnum = 0;
	while (str[i] != '\0')
	{
		if (str[i] != cha)
		{
			wordnum++;
			while (str[i] != cha && str[i] != '\0')
				i++;
			continue ;
		}
		i++;
	}
	return (wordnum);
}

size_t	word_alloc(char const *str, char cha, char **wordptr)
{
	size_t	i;
	size_t	j;
	size_t	u;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != cha)
		{
			u = 0;
			while (str[i + u] != cha && str[i + u] != '\0')
				u++;
			wordptr[j] = (char *)malloc((u + 1) * sizeof(char));
			if (wordptr[j] == NULL)
				return (ft_memfree(wordptr, j), 0);
			j++;
			i = i + u;
			continue ;
		}
		i++;
	}
	return (1);
}

void	word_cpy(char const *str, char cha, char **wordptr)
{
	size_t	i;
	size_t	j;
	size_t	u;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != cha)
		{
			u = 0;
			while (str[i] != cha && str[i] != '\0')
			{
				wordptr[j][u] = str[i];
				i++;
				u++;
			}
			wordptr[j][u] = '\0';
			j++;
			continue ;
		}
		i++;
	}
	wordptr[j] = NULL;
}

char	**ft_split(char const *str, char cha)
{
	size_t	word_num;
	char	**wordptr;

	word_num = count_word(str, cha);
	wordptr = (char **)malloc((word_num + 1) * sizeof(char *));
	if (wordptr == NULL)
		return (NULL);
	if (word_alloc(str, cha, wordptr) == 0)
		return (NULL);
	word_cpy(str, cha, wordptr);
	return (wordptr);
}
