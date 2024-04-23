/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:46:55 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/21 15:37:51 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p;

	p = s;
	while (*p != '\0')
	{
		if (*p == (char)c)
			return ((char *)p);
		++p;
	}
	if ((char)c == '\0')
		return ((char *)p);
	else
		return (NULL);
}
