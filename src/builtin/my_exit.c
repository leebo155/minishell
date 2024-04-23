/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:42 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 17:23:14 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmds_clear(t_cmd **cmd_list_addr);

static void	free_info(t_info *info)
{
	free(info->line);
	free_strs(info->paths);
	free_strs(info->ev);
	free_strs(info->not_ev);
	cmds_clear(&info->cmds);
	free(info->pwd);
	free(info->o_pwd);
	if (info->pipes != 0)
		free(info->pids);
}

static long long	ft_atoll(char *str)
{
	int			i;
	int			flag;
	long long	res;

	res = 0;
	i = 0;
	flag = 1;
	if (str[i] == '+' || str[i] == '-')
		flag *= 44 - str[i++];
	if (str[i] == '\0')
		return (res);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - '0') * flag;
		if (!(res == LLONG_MIN && flag < 0) && res * flag < 0)
			break ;
		++i;
	}
	if (str[i] == '\0')
		str[0] = '0';
	else
		str[0] = 'a';
	return (res);
}

static int	is_nbr(char *str, unsigned char *exit_code)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, " \t\n\v\f\r");
	*exit_code = (unsigned char)ft_atoll(trimmed_str);
	if (ft_isdigit(trimmed_str[0]) == 1)
		return (1);
	free(trimmed_str);
	return (0);
}

int	my_exit(t_info *info, t_cmd *cmd)
{
	unsigned char	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->strs[1] != NULL && is_nbr(cmd->strs[1], &exit_code) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->strs[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	else if (cmd->strs[1] != NULL && cmd->strs[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (cmd->strs[1] == NULL)
		exit_code = 0;
	free_info(info);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
