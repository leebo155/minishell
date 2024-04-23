/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:07:14 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:25:04 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(char **ev)
{
	int		i;
	char	*home_path;

	home_path = NULL;
	i = -1;
	while (ev[++i] != NULL)
	{
		if (ft_strncmp("HOME=", ev[i], 5) == 0)
		{
			home_path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
			break ;
		}
	}
	return (home_path);
}

void	convert_wave(char **ev, char **str_addr)
{
	char	*str;
	char	*new_str;

	str = *str_addr;
	if (ft_strncmp("~", str, 1) == 0)
	{
		if ((str[1] != '\0' && ft_strncmp("/", &str[1], 1) == 0) || \
				str[1] == '\0')
		{
			new_str = get_home_path(ev);
			ft_strattach(&new_str, &str[1]);
			free(str);
			*str_addr = new_str;
		}
	}
}

int	check_input(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		++i;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
