/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:11:45 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:26:53 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' ' && \
			str[i] != '\"' && str[i] != '\'' && str[i] != '=' && \
			str[i] != '-' && str[i] != ':')
		++i;
	return (i);
}

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

static int	sub_dollar_general(char *cur_ev, char **str_addr, \
										int cur_idx, int var_len)
{
	char	*str;
	char	*new_str;
	char	*inner_str;
	char	*second_part;

	str = *str_addr;
	new_str = ft_substr(str, 0, cur_idx);
	second_part = &str[cur_idx + var_len + 1];
	if (cur_ev != NULL)
	{
		inner_str = ft_strdup(&cur_ev[var_len + 1]);
		ft_strattach(&new_str, inner_str);
		cur_idx += ft_strlen(inner_str);
		free(inner_str);
	}
	ft_strattach(&new_str, second_part);
	free(str);
	*str_addr = new_str;
	return (cur_idx);
}

int	dollar_general(t_info *info, char **str_addr, int cur_idx)
{
	int		i;
	int		ev_len;
	int		var_len;
	char	*str;

	str = *str_addr;
	var_len = get_var_len(&str[cur_idx + 1]);
	i = -1;
	while (info->ev[++i] != NULL)
	{
		ev_len = get_ev_len(info->ev[i]);
		if (var_len == ev_len)
			if (ft_strncmp(&str[cur_idx + 1], info->ev[i], ev_len) == 0)
				break ;
	}
	cur_idx = sub_dollar_general(info->ev[i], str_addr, cur_idx, var_len);
	return (cur_idx);
}

void	delete_quotes(char *str)
{
	int		i;
	int		j;
	char	cur_quote;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			cur_quote = str[i];
			j = i + 1;
			while (str[j] != cur_quote)
				j++;
			ft_strlcpy(&str[i], &str[i + 1], strlen(str) - i);
			--j;
			ft_strlcpy(&str[j], &str[j + 1], strlen(str) - j);
			i = j - 1;
		}
	}
}
