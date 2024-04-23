/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:00:22 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/21 21:16:27 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*p1;
	const char	*p2;

	if (dst == NULL && src == NULL)
		return (NULL);
	p1 = dst;
	p2 = src;
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		++i;
	}
	return (dst);
}
