/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_putstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:54:06 by jiryu             #+#    #+#             */
/*   Updated: 2023/01/29 17:54:18 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sub_putstr_fd(char *s, int fd)
{
	int	len;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		len = 6;
	}
	else
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	return (len);
}
