/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:27:12 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:36 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_word_count(char const *s, char c)
{
	int	i;
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c && flag == 1)
			flag = 0;
		else if (s[i] != c && flag == 0)
		{
			flag = 1;
			++count;
		}
	}
	return (count);
}

static int	malloc_guard(char **str, int idx, int size)
{
	str[idx] = (char *)ft_malloc(sizeof(char) * (size + 1));
	if (str[idx] == NULL)
		return (0);
	str[idx][size] = '\0';
	return (1);
}

static int	malloc_words(char const *s, char c, char **res, int i)
{
	int		idx;
	size_t	size;
	int		flag;

	flag = 0;
	idx = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c && flag == 1)
		{
			flag = 0;
			if (malloc_guard(res, ++idx, size) == 0)
				return (0);
		}
		else if (s[i] != c && flag == 0)
		{
			flag = 1;
			size = 1;
		}
		else if (s[i] != c && flag == 1)
			++size;
	}
	if (flag == 1 && malloc_guard(res, ++idx, size) == 0)
		return (0);
	return (1);
}

static void	copy_words(char const *s, char c, char **res)
{
	int	i;
	int	x_idx;
	int	y_idx;
	int	flag;

	flag = 0;
	x_idx = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c && flag == 1)
		{
			flag = 0;
			++x_idx;
		}
		else if (s[i] != c)
		{
			if (flag == 0)
			{
				flag = 1;
				y_idx = -1;
			}
			res[x_idx][++y_idx] = s[i];
		}
	}
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		i;
	char	**res;

	word_count = cal_word_count(s, c);
	res = (char **)ft_malloc(sizeof(char *) * (word_count + 1));
	if (res == NULL)
		return (NULL);
	res[word_count] = NULL;
	if (malloc_words(s, c, res, -1) == 0)
	{
		i = -1;
		while (++i < word_count && res[i] != NULL)
			free(res[i]);
		free(res);
		return (NULL);
	}
	copy_words(s, c, res);
	return (res);
}
