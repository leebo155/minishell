/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:54:44 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/21 22:29:20 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	h_size;
	size_t	n_size;

	if (haystack == NULL && len == 0)
		return (NULL);
	h_size = ft_strlen(haystack);
	n_size = ft_strlen(needle);
	if (n_size == 0)
		return ((char *)haystack);
	i = 0;
	while (i + n_size < h_size + 1 && i + n_size <= len)
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (j < n_size && haystack[i + j] == needle[j])
				++j;
			if (j == n_size)
				return ((char *)&(haystack[i]));
		}
		++i;
	}
	return (NULL);
}
