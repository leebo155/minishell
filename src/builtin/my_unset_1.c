/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:46 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 12:59:50 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_not_ev(t_info *info, t_cmd *cmd);

static int	get_ev_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		++i;
	}
	return (0);
}

static int	search_ev(char **ev, char *str)
{
	int	i;
	int	ev_len;
	int	str_len;

	str_len = ft_strlen(str);
	i = -1;
	while (ev[++i] != NULL)
	{
		ev_len = get_ev_len(ev[i]);
		if (str_len == ev_len && ft_strncmp(ev[i], str, ev_len) == 0)
		{
			ev[i][0] = '\0';
			return (1);
		}
	}
	return (0);
}

static void	get_cnt_ev(char **ev, char **strs, int *ev_size, int *unset_cnt)
{
	int	i;

	i = 0;
	while (ev[i] != NULL)
		++i;
	*ev_size = i + 1;
	*unset_cnt = 0;
	i = 0;
	while (strs[++i] != NULL)
		*unset_cnt += search_ev(ev, strs[i]);
}

static void	unset_ev(t_info *info, t_cmd *cmd)
{
	int		i;
	int		j;
	int		ev_size;
	int		unset_cnt;
	char	**new_ev;

	get_cnt_ev(info->ev, cmd->strs, &ev_size, &unset_cnt);
	if (unset_cnt == 0)
		return ;
	new_ev = (char **)ft_calloc(ev_size - unset_cnt, sizeof(char *));
	i = -1;
	j = -1;
	while (info->ev[++i] != NULL)
	{
		if (info->ev[i][0] != '\0')
			new_ev[++j] = info->ev[i];
		else
			free(info->ev[i]);
	}
	free(info->ev);
	info->ev = new_ev;
}

int	my_unset(t_info *info, t_cmd *cmd)
{
	if (cmd->strs[1] == NULL || cmd->strs[1][0] == '\0')
		return (EXIT_SUCCESS);
	unset_ev(info, cmd);
	unset_not_ev(info, cmd);
	return (EXIT_SUCCESS);
}
