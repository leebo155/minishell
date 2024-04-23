/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:01:58 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:24:40 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(unsigned long size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
	{
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
		exit(1);
	}
	else
		return (res);
}
