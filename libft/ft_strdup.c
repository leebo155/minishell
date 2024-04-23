/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:52:39 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:03:52 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*res;

	size = ft_strlen(s1) + 1;
	res = (char *)ft_malloc(sizeof(char) * size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, size);
	return (res);
}
