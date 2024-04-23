/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:29:38 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 17:29:33 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_input(char **strs);
void	convert_wave(char **ev, char **str_addr);

static char	*get_path(char *str, t_info *info)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (info->ev[++i] != NULL)
	{
		if (ft_strncmp(info->ev[i], str, len) == 0)
			return (ft_substr(info->ev[i], len, ft_strlen(info->ev[i]) - len));
	}
	return (NULL);
}

static int	cd_ev(t_info *info, char *str)
{
	char	*temp;
	char	*path;
	int		ret;

	path = get_path(str, info);
	ret = chdir(path);
	free(path);
	if (ret != 0)
	{
		temp = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(temp, STDERR_FILENO);
		free(temp);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

static void	change_info(t_info *info, t_cmd *cmd)
{
	free(info->o_pwd);
	info->o_pwd = info->pwd;
	info->pwd = getcwd(NULL, sizeof(NULL));
	if (info->pwd == NULL)
	{
		ft_putendl_fd("\
cd: error retrieving current directory: \
getcwd: cannot access parent directories: \
No such file or directory", STDERR_FILENO);
		info->pwd = ft_strdup(info->o_pwd);
		ft_strattach(&info->pwd, "/");
		ft_strattach(&info->pwd, cmd->strs[1]);
	}
}

static void	change_ev(t_info *info)
{
	int		i;
	char	*new_str;

	i = -1;
	while (info->ev[++i] != NULL)
	{
		if (ft_strncmp(info->ev[i], "PWD=", 4) == 0)
		{
			new_str = ft_strdup("PWD=");
			ft_strattach(&new_str, info->pwd);
			free(info->ev[i]);
			info->ev[i] = new_str;
		}
		else if (ft_strncmp(info->ev[i], "OLDPWD=", 7) == 0)
		{
			new_str = ft_strdup("OLDPWD=");
			ft_strattach(&new_str, info->o_pwd);
			free(info->ev[i]);
			info->ev[i] = new_str;
		}
	}
}

int	my_cd(t_info *info, t_cmd *cmd)
{
	int	ret;

	if (check_input(cmd->strs) == 1)
		return (EXIT_FAILURE);
	if (cmd->strs[1] == NULL)
		ret = cd_ev(info, "HOME=");
	else if (ft_strcmp(cmd->strs[1], "-") == 0)
		ret = cd_ev(info, "OLDPWD=");
	else
	{
		convert_wave(info->ev, &cmd->strs[1]);
		ret = chdir(cmd->strs[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd->strs[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_info(info, cmd);
	change_ev(info);
	return (EXIT_SUCCESS);
}
