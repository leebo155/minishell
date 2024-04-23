/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_putptr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:22:36 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 22:01:41 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sub_putptr_fd(unsigned long n, int fd)
{
	int		i;
	int		j;
	char	temp[16];
	char	str[19];

	if (n == 0)
		write(fd, "0x0", 3);
	else
	{
		i = -1;
		while (n > 0)
		{
			temp[++i] = "0123456789abcdef"[n % 16];
			n /= 16;
		}
		++i;
		ft_strlcpy(str, "0x", 3);
		j = 1;
		while (i > 0)
			str[++j] = temp[--i];
		str[++j] = '\0';
		write(fd, str, j);
		return (j);
	}
	return (3);
}
