/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:18:13 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/24 16:46:55 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equal_next_idx(char *str);

bool	is_valid(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~' || c == '-' || c == '?' || c == '&' || c == '*')
		return (0);
	else
		return (1);
}

void	move_strs(char **a, char **b)
{
	int	i;

	i = -1;
	while (b[++i] != NULL)
		a[i] = ft_strdup(b[i]);
	free_strs(b);
}

void	add_not_ev(t_info *info, char *str)
{
	int		i;
	char	**new_strs;

	i = 0;
	while (info->not_ev[i] != NULL && ft_strcmp(info->not_ev[i], str) != 0)
		++i;
	if (info->not_ev[i] != NULL)
		i = -1;
	else
	{
		new_strs = ft_calloc(i + 2, sizeof(char *));
		move_strs(new_strs, info->not_ev);
		info->not_ev = new_strs;
	}
	if (i >= 0)
		info->not_ev[i] = ft_strdup(str);
	str[0] = '\0';
}

int	without_arg(t_info *info)
{
	int		i;
	int		front_len;
	char	*front_str;

	i = -1;
	while (info->ev[++i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		front_len = equal_next_idx(info->ev[i]);
		front_str = ft_substr(info->ev[i], 0, front_len);
		ft_putstr_fd(front_str, STDOUT_FILENO);
		free(front_str);
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putstr_fd(&info->ev[i][front_len], STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	i = -1;
	while (info->not_ev[++i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(info->not_ev[i], STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

void	unset_str(t_info *info, char *str)
{
	int		front_len;
	t_cmd	temp_cmd;

	front_len = equal_next_idx(str);
	temp_cmd.strs = (char **)ft_calloc(3, sizeof(char *));
	temp_cmd.strs[0] = ft_strdup("");
	temp_cmd.strs[1] = ft_substr(str, 0, front_len - 1);
	my_unset(info, &temp_cmd);
	free(temp_cmd.strs[0]);
	free(temp_cmd.strs[1]);
	free(temp_cmd.strs);
}
