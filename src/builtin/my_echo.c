/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:36 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 16:56:47 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lines(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
	{
		ft_putstr_fd(strs[i], STDOUT_FILENO);
		if (strs[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	my_echo(t_info *info, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**strs;
	bool	n_option;

	info = NULL;
	strs = cmd->strs;
	n_option = false;
	i = 0;
	while (strs[++i] != NULL && strs[i][0] == '-' && strs[i][1] == 'n')
	{
		j = 1;
		while (strs[i][j] == 'n')
			++j;
		if (strs[i][j] == '\0')
			n_option = true;
		else
			break ;
	}
	print_lines(&strs[i]);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
