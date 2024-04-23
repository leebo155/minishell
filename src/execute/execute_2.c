/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:08:17 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/24 19:01:18 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_input(t_info *info, t_chunk *heredoc, char *file_name)
{
	int		fd;
	char	*line;

	g_in_heredoc = 1;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (line != NULL && ft_strcmp(heredoc->str, line) != 0 && \
										g_in_heredoc == 1)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	if (g_in_heredoc == 0)
		return (EXIT_FAILURE);
	g_in_heredoc = 0;
	info->heredoc = true;
	return (EXIT_SUCCESS);
}

static char	*get_filename(void)
{
	static int	i;
	char		*nbr;
	char		*file_name;

	nbr = ft_itoa(i++);
	file_name = ft_strdup(".tmp_heredoc_file_");
	ft_strattach(&file_name, nbr);
	free(nbr);
	return (file_name);
}

int	set_heredoc(t_info *info, t_cmd *cmd)
{
	t_chunk	*cur_redirs;

	cur_redirs = cmd->redirs;
	while (cur_redirs != NULL)
	{
		if (cur_redirs->token == D_IN)
		{
			if (cmd->hd_file_name != NULL)
				free(cmd->hd_file_name);
			cmd->hd_file_name = get_filename();
			if (get_input(info, cur_redirs, cmd->hd_file_name) == 1)
			{
				info->error_num = 1;
				return (restart_minishell(info));
			}
		}
		cur_redirs = cur_redirs->next;
	}
	return (EXIT_SUCCESS);
}
