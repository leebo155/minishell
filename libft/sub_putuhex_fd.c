/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_putuhex_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:47:55 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 22:03:11 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sub_putuhex_fd(unsigned int n, int fd)
{
	int		i;
	int		j;
	char	temp[8];
	char	str[9];

	if (n == 0)
		write(fd, "0", 1);
	else
	{
		i = -1;
		while (n > 0)
		{
			temp[++i] = "0123456789ABCDEF"[n % 16];
			n /= 16;
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
