/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:26:38 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 16:04:48 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sub_exception(int n)
{
	size_t	size;
	char	*res;

	if (n == -2147483648)
		size = 12;
	else
		size = 2;
	res = (char *)ft_malloc(sizeof(char) * size);
	if (res == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(res, "-2147483648", size);
	else
		ft_strlcpy(res, "0", size);
	return (res);
}

static char	*sub_itoa(char *temp, int size, int flag)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)ft_malloc(sizeof(char) * (size + flag + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = size - 1;
	if (flag == 1)
	{
		res[i] = '-';
		++i;
	}
	while (i < size + flag)
	{
		res[i] = temp[j];
		++i;
		--j;
	}
	res[i] = '\0';
	return (res);
}

static void	find_size_sign(int n, int *flag, size_t *size, char *temp)
{
	*flag = 0;
	if (n < 0)
	{
		*flag = 1;
		n *= -1;
	}
	*size = 0;
	while (n > 0)
	{
		temp[*size] = n % 10 + '0';
		n /= 10;
		++(*size);
	}
}

char	*ft_itoa(int n)
{
	int		flag;
	size_t	size;
	char	temp[11];
	char	*res;

	if (n == -2147483648 || n == 0)
		return (sub_exception(n));
	find_size_sign(n, &flag, &size, temp);
	res = sub_itoa(temp, size, flag);
	if (res == NULL)
		return (NULL);
	return (res);
}
