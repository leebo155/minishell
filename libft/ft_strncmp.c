/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:56:54 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/21 21:42:59 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (p1[i] != '\0' && p2[i] != '\0' && i < n)
	{
		if (p1[i] != p2[i])
			return ((int)(p1[i] - p2[i]));
		++i;
	}
	if (i < n)
		return ((int)(p1[i] - p2[i]));
	else
		return (0);
}
