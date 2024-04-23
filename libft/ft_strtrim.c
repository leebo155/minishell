/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:46:10 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:11 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_start(char const *s1, char const *set, size_t s_len)
{
	size_t	i;
	size_t	start;
	size_t	set_len;

	set_len = ft_strlen(set);
	start = 0;
	while (start < s_len)
	{
		i = 0;
		while (set[i] != s1[start] && i < set_len)
			++i;
		if (i != set_len)
			++start;
		else
			break ;
	}
	return (start);
}

static int	cal_end(char const *s1, char const *set, size_t s_len)
{
	size_t	i;
	size_t	end;
	size_t	set_len;

	set_len = ft_strlen(set);
	end = s_len - 1;
	while (end < s_len)
	{
		i = 0;
		while (set[i] != s1[end] && i < set_len)
			++i;
		if (i != set_len)
			--end;
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s_len;
	size_t	start;
	size_t	end;
	size_t	size;
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s_len = ft_strlen(s1);
	start = cal_start(s1, set, s_len);
	if (start == s_len)
		size = 0;
	else
	{
		end = cal_end(s1, set, s_len);
		size = end - start + 1;
	}
	res = (char *)ft_malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	else if (size == 0)
		res[0] = '\0';
	else
		ft_strlcpy(res, &(s1[start]), size + 1);
	return (res);
}
