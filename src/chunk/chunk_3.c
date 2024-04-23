/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:33:28 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/24 15:07:29 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_chunk	*chunk_new(char *str, int token)
{
	static int	i;
	t_chunk		*new_chunk;

	new_chunk = (t_chunk *)ft_calloc(1, sizeof(t_chunk));
	new_chunk->str = str;
	new_chunk->token = token;
	new_chunk->idx = i++;
	if (i < 0)
		i = 0;
	new_chunk->next = NULL;
	new_chunk->prev = NULL;
	return (new_chunk);
}

void	chunk_list_push(t_chunk **chunk_list_addr, t_chunk *new_chunk)
{
	t_chunk	*cur_chunk;

	cur_chunk = *chunk_list_addr;
	if (cur_chunk == NULL)
	{
		*chunk_list_addr = new_chunk;
		return ;
	}
	while (cur_chunk->next != NULL)
		cur_chunk = cur_chunk->next;
	cur_chunk->next = new_chunk;
	new_chunk->prev = cur_chunk;
}

int	make_new_chunk(char *str, t_token token, t_chunk **chunk_list)
{
	t_chunk	*new_chunk;

	new_chunk = chunk_new(str, token);
	chunk_list_push(chunk_list, new_chunk);
	return (1);
}

t_token	what_token(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (OUT);
	else if (c == '<')
		return (IN);
	return (0);
}

int	add_token(char *str, t_chunk **chunk_list)
{
	t_token	cur_token;

	cur_token = what_token(str[0]);
	if (cur_token == OUT && what_token(str[1]) == OUT)
	{
		if (make_new_chunk(NULL, D_OUT, chunk_list) == 0)
			return (-1);
		return (2);
	}
	else if (cur_token == IN && what_token(str[1]) == IN)
	{
		if (make_new_chunk(NULL, D_IN, chunk_list) == 0)
			return (-1);
		return (2);
	}
	else if (cur_token != 0)
	{
		if (make_new_chunk(NULL, cur_token, chunk_list) == 0)
			return (-1);
		return (1);
	}	
	return (0);
}
