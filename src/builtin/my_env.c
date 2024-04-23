/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:40 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/22 20:25:08 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_info *info, t_cmd *cmd)
{
	int		i;

	cmd = NULL;
	i = -1;
	while (info->ev[++i] != NULL)
		ft_putendl_fd(info->ev[i], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
