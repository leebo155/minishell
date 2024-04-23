/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:09:57 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 12:49:34 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		free(strs[i]);
	free(strs);
}

char	**strdup_arr(char **strs)
{
	int		i;
	int		cnt;
	char	**res;

	cnt = 0;
	while (strs[cnt] != NULL)
		cnt++;
	res = ft_calloc(sizeof(char *), cnt + 1);
	i = -1;
	while (++i < cnt)
		res[i] = ft_strdup(strs[i]);
	return (res);
}

int	print_error(int code, t_info *info, int is_child)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (code == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", \
			STDERR_FILENO);
	else if (code == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (code == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (code == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (code == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (code == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (code == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (code == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	info->error_num = 2;
	if (is_child == 0)
		return (restart_minishell(info));
	return (EXIT_FAILURE);
}

void	print_message(char *keyword, char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(keyword, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}
