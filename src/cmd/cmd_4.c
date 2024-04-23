/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:08:30 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/25 20:01:47 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	(*builtin_arr(char *str))(t_info *info, t_cmd *cmd)
{
	if (str != NULL)
	{
		if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
			return (my_echo);
		else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
			return (my_env);
		else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
			return (my_exit);
		else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
			return (my_export);
		else if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
			return (my_cd);
		else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
			return (my_pwd);
		else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
			return (my_unset);
	}
	return (NULL);
}

t_cmd	*cmd_new(t_parse_info *parse_info, char **strs)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new_cmd->strs = strs;
	new_cmd->builtin = builtin_arr(strs[0]);
	new_cmd->hd_file_name = NULL;
	new_cmd->num_redirs = parse_info->num_redirs;
	new_cmd->redirs = parse_info->redirs;
	new_cmd->is_outfile = parse_info->is_outfile;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	chunk_clear_print_error(int code, t_info *info, t_chunk *chunk_list)
{
	chunk_list_clear(&chunk_list);
	print_error(code, info, 0);
}

void	cmd_list_push(t_cmd **cmd_list_addr, t_cmd *new_cmd)
{
	t_cmd	*cur_cmd;

	cur_cmd = *cmd_list_addr;
	if (cur_cmd == NULL)
	{
		*cmd_list_addr = new_cmd;
		return ;
	}
	while (cur_cmd->next != NULL)
		cur_cmd = cur_cmd->next;
	cur_cmd->next = new_cmd;
	new_cmd->prev = cur_cmd;
}
