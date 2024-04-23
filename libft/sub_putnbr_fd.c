/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_putnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:58:37 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 19:28:19 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sub_itoa(char *str, int n)
{
	int		i;
	int		j;
	int		flag;
	char	temp[12];

	i = -1;
	flag = 0;
	if (n < 0)
	{
		flag = 1;
		n *= -1;
	}
	while (n > 0)
	{
		temp[++i] = n % 10 + '0';
		n /= 10;
	}
	if (flag == 1)
		temp[++i] = '-';
	j = -1;
	++i;
	while (i > 0)
		str[++j] = temp[--i];
	str[++j] = '\0';
	return (j);
}

int	sub_putnbr_fd(int n, int fd)
{
	int		len;
	char	str[12];

	if (n == -2147483648)
	{
		len = 11;
		ft_strlcpy(str, "-2147483648", len + 1);
	}
	else if (n == 0)
	{
		len = 1;
		ft_strlcpy(str, "0", len + 1);
	}
	else
		len = sub_itoa(str, n);
	write(fd, str, len);
	return (len);
}
