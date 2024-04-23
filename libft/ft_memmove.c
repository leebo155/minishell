/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:26:42 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/22 18:46:32 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*p1;
	const char	*p2;

	if (dst == NULL && src == NULL)
		return (dst);
	p1 = dst;
	p2 = src;
	if (p1 > p2)
	{
		i = len;
		while (--i < len)
			p1[i] = p2[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			p1[i] = p2[i];
			++i;
		}
	}
	return (dst);
}
