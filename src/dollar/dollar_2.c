/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:12:11 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 17:12:09 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_general(t_info *info, char **str_addr, int cur_idx);

static int	find_dollar_idx(char *str, int cur_idx, int *s_cnt, int *d_cnt)
{
	int	i;

	i = cur_idx - 1;
	while (str[++i] != '\0')
	{
		if (*s_cnt % 2 == 0)
		{
			if (str[i] == '\"')
				++(*d_cnt);
			else if (str[i] == '$' && str[i + 1] != '=' && \
					str[i + 1] != '%' && str[i + 1] != '^' && \
					str[i + 1] != '/' && str[i + 1] != '\'' )
				break ;
		}
		if (*d_cnt % 2 == 0)
			if (str[i] == '\'')
				++(*s_cnt);
	}
	return (i);
}

static int	dollar_digit(char **str_addr, int cur_idx)
{
	char	*str;
	char	*new_str;

	str = *str_addr;
	new_str = ft_substr(str, 0, cur_idx);
	ft_strattach(&new_str, &str[cur_idx + 2]);
	free(str);
	*str_addr = new_str;
	return (cur_idx);
}

static int	dollar_question(char **str_addr, int cur_idx, int error_num)
{
	char	*str;
	char	*new_str;
	char	*nbr;

	str = *str_addr;
	new_str = ft_substr(str, 0, cur_idx);
	nbr = ft_itoa(error_num);
	ft_strattach(&new_str, nbr);
	ft_strattach(&new_str, &str[cur_idx + 2]);
	free(*str_addr);
	cur_idx += ft_strlen(nbr);
	free(nbr);
	*str_addr = new_str;
	return (cur_idx);
}

void	dollar_all(t_info *info, char **str_addr)
{
	int		i;
	int		s_cnt;
	int		d_cnt;
	char	*str;

	str = *str_addr;
	s_cnt = 0;
	d_cnt = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i = find_dollar_idx(str, i, &s_cnt, &d_cnt);
		if (str[i] == '$' && ft_isdigit(str[i + 1]) == 1)
			i = dollar_digit(&str, i);
		else if (str[i] == '$' && str[i + 1] == '?')
			i = dollar_question(&str, i, info->error_num);
		else if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ' && \
				!(str[i + 1] == '\"' && str[i + 2] == '\0'))
			i = dollar_general(info, &str, i);
		else
			++i;
	}
	*str_addr = str;
}
