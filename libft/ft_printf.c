/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:36:39 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 22:31:38 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sub_printf(char c, va_list ap, int *res)
{
	if (c == 'c')
		*res += sub_putchar_fd(va_arg(ap, int), 1);
	else if (c == 's')
		*res += sub_putstr_fd(va_arg(ap, char *), 1);
	else if (c == 'p')
		*res += sub_putptr_fd(va_arg(ap, long), 1);
	else if (c == 'd' || c == 'i')
		*res += sub_putnbr_fd(va_arg(ap, int), 1);
	else if (c == 'u')
		*res += sub_putunbr_fd(va_arg(ap, int), 1);
	else if (c == 'x')
		*res += sub_putlhex_fd(va_arg(ap, int), 1);
	else if (c == 'X')
		*res += sub_putuhex_fd(va_arg(ap, int), 1);
	else if (c == '%')
		*res += write(1, "%%", 1);
	else
		return (-1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		start;
	int		res;
	va_list	ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	i = -1;
	start = 0;
	res = 0;
	while (1)
	{
		if (format[++i] == '%' || format[i] == '\0')
		{
			res += write(1, &format[start], i - start);
			if (format[i] == '\0')
				break ;
			start = i + 2;
			if (sub_printf(format[++i], ap, &res) == -1)
				return (-1);
		}
	}
	va_end(ap);
	return (res);
}
