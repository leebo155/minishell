/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:09:52 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:18 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	size;
	char	*res;

	s_len = ft_strlen(s);
	if (start >= s_len)
		size = 0;
	else
		size = s_len - start;
	if (size > len)
		size = len;
	res = (char *)ft_malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	if (start >= s_len)
		res[0] = '\0';
	else
		ft_strlcpy(res, &(s[start]), size + 1);
	return (res);
}
