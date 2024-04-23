/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strattach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:50:44 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:21 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strattach(char **s1_adr, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	size;
	char	*temp;

	if (*s1_adr != NULL)
		len1 = ft_strlen(*s1_adr);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	size = len1 + len2 + 1;
	temp = (char *)ft_malloc(sizeof(char) * size);
	if (temp == NULL)
		return (-1);
	if (*s1_adr != NULL)
	{
		ft_strlcpy(temp, *s1_adr, len1 + 1);
		ft_strlcat(temp, s2, size);
		free(*s1_adr);
	}
	else
		ft_strlcpy(temp, s2, size);
	*s1_adr = temp;
	return (0);
}
