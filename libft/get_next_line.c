/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:41:39 by jiryu             #+#    #+#             */
/*   Updated: 2023/04/06 13:56:40 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	sub_get_index(const char *s, int idx, int mode)
{
	if (mode == 0)
	{
		while (idx < BUFFER_SIZE)
		{
			if (s[idx] != '\0')
				return (idx);
			++idx;
		}
	}
	else if (mode == 1)
	{
		while (idx < BUFFER_SIZE)
		{
			if (s[idx] == '\n')
				return (idx);
			else if (s[idx] == '\0')
				return (idx - 1);
			++idx;
		}
	}
	return (idx);
}

static int	process_buffer(t_list *cur, char **res_adr)
{
	int	i;

	cur->start = sub_get_index(cur->buffer, 0, 0);
	if (cur->start == BUFFER_SIZE)
		return (3);
	cur->end = sub_get_index(cur->buffer, cur->start, 1);
	if (cur->end != BUFFER_SIZE)
	{
		if (sub_strjoin(res_adr, cur, cur->end - cur->start + 1) == -1)
			return (-1);
		i = -1;
		while (++i < cur->end - cur->start + 1)
			cur->buffer[cur->start + i] = '\0';
		return (1);
	}
	else
	{
		if (sub_strjoin(res_adr, cur, cur->end - cur->start) == -1)
			return (-1);
		i = -1;
		while (++i < cur->end - cur->start)
			cur->buffer[cur->start + i] = '\0';
		return (2);
	}
}

static void	sub_gnl(t_list **buffers_adr, t_list *cur, char **res_adr, int fd)
{
	ssize_t	count;
	int		flag;

	count = read(fd, cur->buffer, BUFFER_SIZE);
	while (count > 0)
	{
		flag = process_buffer(cur, res_adr);
		if (flag != 2)
			break ;
		count = read(fd, cur->buffer, BUFFER_SIZE);
	}
	if (count < 0)
		flag = -1;
	if (count == 0 || flag == -1)
		sub_free(buffers_adr, cur, res_adr, flag);
	return ;
}

static t_list	*sub_init_find(t_list **buffers_adr, int fd)
{
	t_list	*temp;
	int		i;

	temp = *buffers_adr;
	while (temp != NULL && temp->fd != fd)
		temp = temp->next;
	if (temp != NULL && temp->fd == fd)
		return (temp);
	temp = (t_list *)malloc(sizeof(t_list));
	if (temp == NULL)
		return (NULL);
	temp->buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (temp->buffer == NULL)
	{
		free(temp);
		return (NULL);
	}
	i = -1;
	while (++i < BUFFER_SIZE)
		temp->buffer[i] = '\0';
	temp->fd = fd;
	temp->next = *buffers_adr;
	*buffers_adr = temp;
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_list	*buffers;
	t_list			*cur;
	char			*res;
	int				flag;

	if (fd < 0)
		return (NULL);
	cur = sub_init_find(&buffers, fd);
	if (cur == NULL)
		return (NULL);
	res = NULL;
	if (cur->buffer != NULL)
	{
		flag = process_buffer(cur, &res);
		if (flag == -1)
		{
			sub_free(&buffers, cur, &res, flag);
			return (NULL);
		}
		if (flag == 1)
			return (res);
	}
	sub_gnl(&buffers, cur, &res, fd);
	return (res);
}

// #include<fcntl.h>
// #include<stdio.h>
// #include<time.h>
// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	clock_t start, end;
// 	start = clock();
// 	char *line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("%s",line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	end = clock();
// 	double res = (double)(end - start)/CLOCKS_PER_SEC;
// 	printf("\ntime:%f\n", res);
// }