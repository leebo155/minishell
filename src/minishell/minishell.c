/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:36:41 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 18:41:40 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char *line);
int		make_chunks(t_info *info);
int		make_cmds(t_info *info);
void	execute_single(t_info *info, t_cmd *cmd);
void	execute(t_info *info);
void	init_info_global(t_info *info);

static void	chunks_clear(t_chunk **chunk_list_addr)
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

static void	prepare_executor(t_info *info)
{
	if (info->pipes == 0)
		execute_single(info, info->cmds);
	else
	{
		info->pids = ft_calloc(sizeof(int), info->pipes + 2);
		execute(info);
	}
}

void	cmds_clear(t_cmd **cmd_list_addr)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	t_chunk	*cur_redirs;

	cur_cmd = *cmd_list_addr;
	if (cur_cmd == NULL)
		return ;
	while (cur_cmd != NULL)
	{
		next_cmd = cur_cmd->next;
		cur_redirs = cur_cmd->redirs;
		chunks_clear(&cur_redirs);
		if (cur_cmd->strs != NULL)
			free_strs(cur_cmd->strs);
		if (cur_cmd->hd_file_name != NULL)
			free(cur_cmd->hd_file_name);
		free(cur_cmd);
		cur_cmd = next_cmd;
	}
	*cmd_list_addr = NULL;
}

int	minishell(t_info *info)
{
	char	*temp;

	info->line = readline("minishell$ ");
	if (info->line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (info->line[0] != '\0')
		add_history(info->line);
	temp = ft_strtrim(info->line, " ");
	free(info->line);
	info->line = temp;
	if (info->line[0] == '\0')
		return (restart_minishell(info));
	if (check_quotes(info->line) == EXIT_FAILURE)
		return (print_error(2, info, 0));
	if (make_chunks(info) == EXIT_FAILURE)
		return (print_error(1, info, 0));
	make_cmds(info);
	prepare_executor(info);
	return (restart_minishell(info));
}

int	restart_minishell(t_info *info)
{
	cmds_clear(&info->cmds);
	free(info->line);
	if (info->pids)
		free(info->pids);
	free_strs(info->paths);
	init_info_global(info);
	info->reset = true;
	minishell(info);
	return (EXIT_SUCCESS);
}
