/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:18:37 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/25 22:20:25 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_not_ev(char **not_ev, char *str)
{
	int	i;

	i = -1;
	while (not_ev[++i] != NULL)
	{
		if (ft_strcmp(not_ev[i], str) == 0)
		{
			not_ev[i][0] = '\0';
			return (1);
		}
	}
	return (0);
}

static void	get_cnt_not_ev(char **not_ev, char **strs, int *not_ev_size, \
														int *unset_cnt)
{
	int	i;

	i = 0;
	while (not_ev[i] != NULL)
		++i;
	*not_ev_size = i + 1;
	*unset_cnt = 0;
	i = 0;
	while (strs[++i] != NULL)
		*unset_cnt += search_not_ev(not_ev, strs[i]);
}

void	unset_not_ev(t_info *info, t_cmd *cmd)
{
	int		i;
	int		j;
	int		not_ev_size;
	int		unset_cnt;
	char	**new_not_ev;

	get_cnt_not_ev(info->not_ev, cmd->strs, &not_ev_size, &unset_cnt);
	if (unset_cnt == 0)
		return ;
	new_not_ev = (char **)ft_calloc(not_ev_size - unset_cnt, sizeof(char *));
	i = -1;
	j = -1;
	while (info->not_ev[++i] != NULL)
	{
		if (info->not_ev[i][0] != '\0')
			new_not_ev[++j] = info->not_ev[i];
		else
			free(info->not_ev[i]);
	}
	free(info->not_ev);
	info->not_ev = new_not_ev;
}
