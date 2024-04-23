/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:43:39 by jiryu             #+#    #+#             */
/*   Updated: 2023/04/06 14:04:44 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	sub_putchar_fd(char c, int fd);
int	sub_putstr_fd(char *s, int fd);
int	sub_putnbr_fd(int n, int fd);
int	sub_putunbr_fd(unsigned int n, int fd);
int	sub_putlhex_fd(unsigned int n, int fd);
int	sub_putuhex_fd(unsigned int n, int fd);
int	sub_putptr_fd(unsigned long n, int fd);

#endif
