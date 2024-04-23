/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:09:31 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:25:38 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_token(char *str, t_chunk **chunk_list_addr);
t_token	what_token(char c);

static int	count_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	return (i);
}

static int	skip_quotes(char *str, char del)
{
	int	i;

	i = 0;
	if (str[i] == del)
	{
		++i;
		while (str[i] != del)
			++i;
		++i;
	}
	return (i);
}

static int	add_words(char *str, t_chunk **chunk_list)
{
	int	i;
	int	skip_cnt;

	i = 0;
	while (str[i] != '\0' && what_token(str[i]) == 0)
	{
		if (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
			break ;
		skip_cnt = skip_quotes(&str[i], '\'');
		skip_cnt += skip_quotes(&str[i], '\"');
		if (skip_cnt == 0)
			++i;
		else
			i += skip_cnt;
	}
	if (make_new_chunk(ft_substr(str, 0, i), 0, chunk_list) == 0)
		return (-1);
	return (i);
}

int	make_chunks(t_info *info)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (info->line[i] != '\0')
	{
		i += count_white_spaces(&info->line[i]);
		if (what_token(info->line[i]) != 0)
			ret = add_token(&info->line[i], &info->chunk_list);
		else
			ret = add_words(&info->line[i], &info->chunk_list);
		if (ret < 0)
			return (EXIT_FAILURE);
		i += ret;
	}
	return (EXIT_SUCCESS);
}
