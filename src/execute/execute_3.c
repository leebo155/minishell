/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:51:43 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 12:53:17 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_message(filename, "No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		print_message("", "pipe error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	set_outfile(t_chunk *redirs)
{
	int	fd;

	if (redirs->token == D_OUT)
		fd = open(redirs->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirs->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redirs->str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		print_message("", "pipe error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	set_redirections(t_cmd *cmd)
{
	t_chunk	*cur_redirs;

	cur_redirs = cmd->redirs;
	while (cur_redirs != NULL)
	{
		if (cur_redirs->token == IN)
		{
			if (set_infile(cur_redirs->str) == 1)
				return (EXIT_FAILURE);
		}
		else if (cur_redirs->token == OUT || cur_redirs->token == D_OUT)
		{
			if (set_outfile(cur_redirs) == 1)
				return (EXIT_FAILURE);
		}
		else if (cur_redirs->token == D_IN)
		{
			if (set_infile(cmd->hd_file_name) == 1)
				return (EXIT_FAILURE);
		}
		cur_redirs = cur_redirs->next;
	}
	return (EXIT_SUCCESS);
}
