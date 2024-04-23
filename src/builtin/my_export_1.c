/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:49 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 17:26:56 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		equal_next_idx(char *str);
bool	is_valid(char c);
void	move_strs(char **a, char **b);
void	add_not_ev(t_info *info, char *str);
int		without_arg(t_info *info);
void	unset_str(t_info *info, char *str);

int	export_error(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\': is ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	check_ev(char **ev, char *str)
{
	int		i;
	int		len_with_equal;

	i = -1;
	while (ev[++i] != NULL)
	{
		len_with_equal = equal_next_idx(ev[i]);
		if (ft_strncmp(ev[i], str, len_with_equal) == 0)
		{
			free(ev[i]);
			ev[i] = ft_strdup(str);
			return (1);
		}
		else if (ft_strncmp(ev[i], str, len_with_equal - 1) == 0)
			return (1);
	}
	return (0);
}

static int	check_str(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) == 1)
		return (export_error(str));
	if (str[0] == '=')
		return (export_error(str));
	i = -1;
	while (str[++i] != '\0' && str[i] != '=')
		if (is_valid(str[i]) == 0)
			return (export_error(str));
	return (EXIT_SUCCESS);
}

static int	get_cnt(t_info *info, char **strs, int *ev_size, int *add_cnt)
{
	int		i;

	i = 0;
	while (info->ev[i] != NULL)
		++i;
	*ev_size = i + 1;
	*add_cnt = 0;
	i = 0;
	while (strs[++i] != NULL)
	{
		if (check_str(strs[i]) == 1)
			return (EXIT_FAILURE);
		else if (check_ev(info->ev, strs[i]) == 1)
			strs[i][0] = '\0';
		else if (equal_next_idx(strs[i]) == 0)
			add_not_ev(info, strs[i]);
		else
		{
			unset_str(info, strs[i]);
			++(*add_cnt);
		}
	}
	return (EXIT_SUCCESS);
}

int	my_export(t_info *info, t_cmd *cmd)
{
	int		i;
	int		j;
	int		ev_size;
	int		add_cnt;
	char	**new_ev;

	if (cmd->strs[1] == NULL || cmd->strs[1][0] == '\0')
		return (without_arg(info));
	if (get_cnt(info, cmd->strs, &ev_size, &add_cnt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_ev = (char **)ft_calloc(ev_size + add_cnt, sizeof(char *));
	move_strs(new_ev, info->ev);
	info->ev = new_ev;
	i = 0;
	j = ev_size - 2;
	while (cmd->strs[++i] != NULL)
		if (cmd->strs[i][0] != '\0')
			info->ev[++j] = ft_strdup(cmd->strs[i]);
	return (EXIT_SUCCESS);
}
