/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:36:02 by musoysal          #+#    #+#             */
/*   Updated: 2024/10/25 18:56:13 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_memory(char **arr, size_t index)
{
	while (index > 0)
	{
		free(arr[index - 1]);
		index--;
	}
	free(arr);
}

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	size_t	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s == c)
			word = 0;
		else if (word == 0)
		{
			word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**fill_result(char **result, char const *s, char c, size_t count)
{
	size_t		i;
	char const	*start;

	i = 0;
	while (*s && i < count)
	{
		while (*s == c && *s)
			s++;
		start = s;
		while (*s != c && *s)
			s++;
		if (start < s)
		{
			result[i] = ft_substr(start, 0, s - start);
			if (!result[i++])
				return (free_memory(result, i - 1), NULL);
		}
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;

	if (!s)
		return (NULL);
	count = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (fill_result(result, s, c, count));
}
