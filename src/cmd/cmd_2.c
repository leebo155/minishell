/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:40:14 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:25:51 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_chunk(t_chunk **chunk_addr)
{
	if ((*chunk_addr)->str != NULL)
	{
		free((*chunk_addr)->str);
		(*chunk_addr)->str = NULL;
	}
	free(*chunk_addr);
	*chunk_addr = NULL;
}

static void	sub_chunk_list_erase(t_chunk **chunk_list_addr, int key)
{
	t_chunk	*cur_chunk;
	t_chunk	*pre_chunk;

	cur_chunk = *chunk_list_addr;
	while (cur_chunk != NULL && cur_chunk->idx != key)
	{
		pre_chunk = cur_chunk;
		cur_chunk = cur_chunk->next;
	}
	if (cur_chunk != NULL)
		pre_chunk->next = cur_chunk->next;
	else
		pre_chunk->next = NULL;
	if (pre_chunk->next != NULL)
		pre_chunk->next->prev = pre_chunk;
	free_chunk(&cur_chunk);
}

void	chunk_list_erase(t_chunk **chunk_list_addr, int key)
{
	t_chunk	*first_chunk;

	first_chunk = *chunk_list_addr;
	if (first_chunk->idx == key)
	{
		*chunk_list_addr = first_chunk->next;
		if (*chunk_list_addr != NULL)
			(*chunk_list_addr)->prev = NULL;
		free_chunk(&first_chunk);
		return ;
	}
	sub_chunk_list_erase(chunk_list_addr, key);
}

void	chunk_list_clear(t_chunk **chunk_list_addr)
{
	t_chunk	*cur_chunk;
	t_chunk	*next_chunk;

	cur_chunk = *chunk_list_addr;
	if (cur_chunk == NULL)
		return ;
	while (cur_chunk != NULL)
	{
		next_chunk = cur_chunk->next;
		if (cur_chunk->str != NULL)
			free(cur_chunk->str);
		free(cur_chunk);
		cur_chunk = next_chunk;
	}
	*chunk_list_addr = NULL;
}
