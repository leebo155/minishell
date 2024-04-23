/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:53:16 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/21 21:14:07 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		cc;
	const char	*p;

	p = s;
	cc = c;
	i = 0;
	while (i < n)
	{
		if (p[i] == cc)
			return ((void *)(s + i));
		++i;
	}
	return (NULL);
}
