/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:07:14 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:25:31 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	distance_to_pair(char *line, int *cnt, char q)
{
	int	i;

	i = 1;
	++(*cnt);
	while (line[i] != '\0' && line[i] != q)
		++i;
	if (line[i] == q)
	{
		++(*cnt);
		++i;
	}
	return (i);
}

int	check_quotes(char *line)
{
	int	i;
	int	pre_idx;
	int	s_cnt;
	int	d_cnt;

	s_cnt = 0;
	d_cnt = 0;
	i = 0;
	while (line[i] != '\0')
	{
		pre_idx = i;
		if (line[i] == '\'')
			i += distance_to_pair(&line[i], &s_cnt, '\'');
		if (line[i] == '\"')
			i += distance_to_pair(&line[i], &d_cnt, '\"');
		if (pre_idx == i)
			++i;
	}
	if (s_cnt % 2 == 1 || d_cnt % 2 == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
