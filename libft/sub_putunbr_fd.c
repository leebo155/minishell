/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_putunbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:37:46 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 22:03:38 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sub_putunbr_fd(unsigned int n, int fd)
{
	int		i;
	int		j;
	char	temp[10];
	char	str[11];

	if (n == 0)
		write(fd, "0", 1);
	else
	{
		i = -1;
		while (n > 0)
		{
			temp[++i] = n % 10 + '0';
			n /= 10;
		}
		j = -1;
		++i;
		while (i > 0)
			str[++j] = temp[--i];
		str[++j] = '\0';
		write(fd, str, j);
		return (j);
	}
	return (1);
}
