/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:11:40 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 16:55:55 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_all(t_info *info, char **str_addr);
void	delete_quotes(char *str);

static int	find_dollar_next_idx(char *str)
{
	int	s_cnt;
	int	d_cnt;
	int	i;

	i = -1;
	s_cnt = 0;
	d_cnt = 0;
	while (str[++i] != '\0')
	{
		if (s_cnt % 2 == 0)
		{
			if (str[i] == '\"')
				++d_cnt;
			else if (str[i] == '$')
				return (i + 1);
		}
		if (d_cnt % 2 == 0)
			if (str[i] == '\'')
				++s_cnt;
	}
	return (0);
}

static int	delete_this_str(t_cmd *cmd, int cur_idx)
{
	int		i;
	char	**new_strs;

	i = 0;
	while (cmd->strs[i] != NULL)
		++i;
	if (i == 1)
		return (-1);
	new_strs = (char **)ft_calloc(i, sizeof(char *));
	i = -1;
	while (++i < cur_idx)
		new_strs[i] = ft_strdup(cmd->strs[i]);
	while (cmd->strs[i + 1] != NULL)
	{
		new_strs[i] = ft_strdup(cmd->strs[i + 1]);
		++i;
	}
	free_strs(cmd->strs);
	cmd->strs = new_strs;
	return (0);
}

static int	dollar_strs(t_info *info, t_cmd *cmd)
{
	int	i;
	int	dollar_next_idx;
	int	is_empty_str;

	i = 0;
	while (cmd->strs[i] != NULL)
	{
		is_empty_str = 0;
		if (cmd->strs[i][0] == '\0')
			is_empty_str = 1;
		dollar_next_idx = find_dollar_next_idx(cmd->strs[i]);
		if (dollar_next_idx != 0 && cmd->strs[i][dollar_next_idx] != '\0')
			dollar_all(info, &cmd->strs[i]);
		if (is_empty_str == 0 && cmd->strs[i][0] == '\0')
		{
			if (delete_this_str(cmd, i) == -1)
				return (-1);
			continue ;
		}
		delete_quotes(cmd->strs[i]);
		++i;
	}
	return (0);
}

static void	dollar_str(t_info *info, char **str_addr)
{
	int		dollar_next_idx;
	char	*str;

	str = *str_addr;
	dollar_next_idx = find_dollar_next_idx(str);
	if (dollar_next_idx != 0 && str[dollar_next_idx] != '\0')
		dollar_all(info, str_addr);
	delete_quotes(str);
}

int	expand_dollar(t_info *info, t_cmd *cmd)
{
	t_chunk	*cur_redirs;

	if (dollar_strs(info, cmd) == -1)
		return (-1);
	cur_redirs = cmd->redirs;
	while (cur_redirs != NULL)
	{
		if (cur_redirs->token != D_IN)
			dollar_str(info, &cur_redirs->str);
		cur_redirs = cur_redirs->next;
	}
	return (0);
}
