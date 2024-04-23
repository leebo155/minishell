/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:17:38 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:59 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	res = (char *)ft_malloc(count * size);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		res[i] = 0;
		++i;
	}
	return ((void *)res);
}
