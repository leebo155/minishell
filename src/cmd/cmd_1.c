/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:26:48 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/25 23:29:51 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_parse_info *parse_info);
void	cmd_list_push(t_cmd **cmd_list_addr, t_cmd *new_cmd);

static void	get_pipe_cnt(t_chunk *chunk_list, t_info *info)
{
	t_chunk	*temp;

	temp = chunk_list;
	info->pipes = 0;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			info->pipes++;
		temp = temp->next;
	}
}

static int	check_double_pipe(t_info *info, t_token token)
{
	if (token == PIPE)
	{
		print_token_error(info, info->chunk_list, info->chunk_list->token);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_empty_list(t_info *info)
{
	if (info->chunk_list == NULL)
	{
		chunk_clear_print_error(0, info, info->chunk_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_parse_info	init_parse_info(t_chunk *chunk_list, t_info *info)
{
	t_parse_info	temp;

	temp.chunk_list = chunk_list;
	temp.redirs = NULL;
	temp.is_outfile = false;
	temp.num_redirs = 0;
	temp.info = info;
	return (temp);
}

int	make_cmds(t_info *info)
{
	t_cmd			*new_cmd;
	t_parse_info	parse_info;

	info->cmds = NULL;
	get_pipe_cnt(info->chunk_list, info);
	if (info->chunk_list->token == PIPE)
		return (print_token_error(info, info->chunk_list, \
								info->chunk_list->token));
	while (info->chunk_list != NULL)
	{
		if (info->chunk_list->token == PIPE)
			chunk_list_erase(&info->chunk_list, info->chunk_list->idx);
		if (check_empty_list(info) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (check_double_pipe(info, info->chunk_list->token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		parse_info = init_parse_info(info->chunk_list, info);
		new_cmd = init_cmd(&parse_info);
		cmd_list_push(&info->cmds, new_cmd);
		info->chunk_list = parse_info.chunk_list;
	}
	return (EXIT_SUCCESS);
}
