/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wh_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:22 by joklein           #+#    #+#             */
/*   Updated: 2025/03/27 12:24:35 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

static size_t	count_word(char const *str)
{
	size_t	wordnum;
	size_t	i;

	i = 0;
	wordnum = 0;
	while (str[i] != '\0')
	{
		if (!wh_space(str[i]))
		{
			wordnum++;
			while (str[i] != '\0' && !wh_space(str[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (wordnum);
}

static size_t	word_alloc(char const *str, char **wordptr)
{
	size_t	i;
	size_t	j;
	size_t	u;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (!wh_space(str[i]))
		{
			u = 0;
			while (str[i + u] != '\0' && !wh_space(str[i + u]))
				u++;
			wordptr[j] = (char *)malloc((u + 1) * sizeof(char));
			if (wordptr[j] == NULL)
				return (ft_memfree(wordptr), 0);
			j++;
			i = i + u;
			continue ;
		}
		i++;
	}
	return (1);
}

static void	word_cpy(char const *str, char **wordptr)
{
	size_t	i;
	size_t	j;
	size_t	u;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (!wh_space(str[i]))
		{
			u = 0;
			while (str[i] != '\0' && !wh_space(str[i]))
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

char	**ft_split_whspace(char const *str)
{
	size_t	word_num;
	char	**wordptr;

	word_num = count_word(str);
	wordptr = (char **)malloc((word_num + 1) * sizeof(char *));
	if (wordptr == NULL)
		return (NULL);
	if (word_alloc(str, wordptr) == 0)
		return (NULL);
	word_cpy(str, wordptr);
	return (wordptr);
}
