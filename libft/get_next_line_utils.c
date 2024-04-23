/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:09:05 by jiryu             #+#    #+#             */
/*   Updated: 2023/04/06 13:56:45 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	sub_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	sub_strlcat(char *dst, const char *src, int len2, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = len2;
	if (dst == NULL && dstsize == 0)
		return (dstsize + src_len);
	dst_len = sub_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (i < dstsize - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		++i;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

void	sub_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		++i;
	}
	if (dstsize != 0)
		dst[i] = '\0';
}

int	sub_strjoin(char **res, t_list *cur, size_t len2)
{
	char	*temp;
	char	*src;
	size_t	len1;
	size_t	size;

	src = &cur->buffer[cur->start];
	if (*res != NULL)
		len1 = sub_strlen(*res);
	else
		len1 = 0;
	size = len1 + len2 + 1;
	temp = (char *)malloc(sizeof(char) * size);
	if (temp == NULL)
		return (-1);
	if (*res != NULL)
	{
		sub_strlcpy(temp, *res, len1 + 1);
		sub_strlcat(temp, src, len2, size);
		free(*res);
	}
	else
		sub_strlcpy(temp, src, size);
	*res = temp;
	return (0);
}

void	sub_free(t_list **buffers_adr, t_list *cur, char **res_adr, int flag)
{
	t_list	*ptr;

	if (flag == -1 && *res_adr != NULL)
	{
		free(*res_adr);
		*res_adr = NULL;
	}
	if (cur->buffer != NULL)
	{	
		free(cur->buffer);
		cur->buffer = NULL;
	}
	if (*buffers_adr == cur)
		*buffers_adr = cur->next;
	else
	{
		ptr = *buffers_adr;
		while (ptr->next != cur)
			ptr = ptr->next;
		ptr->next = cur->next;
	}
	free(cur);
}
