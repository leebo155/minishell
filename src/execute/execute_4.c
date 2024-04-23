/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:59:37 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 18:43:44 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit_with_msg(int signal);
int		set_redirections(t_cmd *cmd);

static int	check_cmd(char *file_name, char **strs, char **ev)
{
	struct stat	file_stat;

	if (*strs == file_name && access(file_name, F_OK) != 0)
	{
		print_message(file_name, "No such file or directory", STDERR_FILENO);
		return (127);
	}
	if (stat(file_name, &file_stat) == 0 && S_ISDIR(file_stat.st_mode) == 1)
	{
		print_message(file_name, "Is a directory", STDERR_FILENO);
		return (126);
	}
	if (access(file_name, X_OK) == 0)
	{
		execve(file_name, strs, ev);
		return (EXIT_SUCCESS);
	}
	else
	{
		print_message(file_name, "Permission denied", STDERR_FILENO);
		return (126);
	}
}

static int	run_cmd(t_cmd *cmd, t_info *info)
{
	int		i;
	int		j;
	char	*fixed_file_name;

	i = 0;
	while (cmd->strs[i] != NULL && cmd->strs[i][0] == '\0')
		++i;
	if (cmd->strs[i] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strchr(cmd->strs[i], '/') != NULL)
		return (check_cmd(cmd->strs[i], &cmd->strs[i], info->ev));
	j = -1;
	while (info->paths[++j] != NULL)
	{
		fixed_file_name = ft_strjoin(info->paths[j], cmd->strs[i]);
		if (access(fixed_file_name, F_OK) == 0)
			return (check_cmd(fixed_file_name, &cmd->strs[i], info->ev));
		free(fixed_file_name);
	}
	print_message(cmd->strs[i], "command not found", STDERR_FILENO);
	return (127);
}

void	execute_cmd(t_info *info, t_cmd *cmd)
{
	int	exit_code;
	int	null_fd;

	exit_code = 0;
	if (cmd->redirs != NULL)
		if (set_redirections(cmd) == EXIT_FAILURE)
			exit(1);
	if (cmd->builtin != NULL)
	{
		if (info->pipes == 0)
		{
			null_fd = open("/dev/null", O_WRONLY);
			if (cmd->is_outfile == false)
			{
				dup2(null_fd, STDERR_FILENO);
				dup2(null_fd, STDOUT_FILENO);
			}
		}
		exit_code = cmd->builtin(info, cmd);
	}
	else
		exit_code = run_cmd(cmd, info);
	exit(exit_code);
}

void	fork_execute(t_info *info, t_cmd *cmd, int end[2], int fd_in)
{
	static int	i;

	if (info->reset == true)
	{
		i = 0;
		info->reset = false;
	}
	info->pids[i] = fork();
	if (info->pids[i] < 0)
		print_error(5, info, 0);
	if (info->pids[i] == 0)
	{
		if (cmd->prev != NULL && dup2(fd_in, STDIN_FILENO) < 0)
			print_error(4, info, 1);
		close(end[0]);
		if (cmd->next != NULL && dup2(end[1], STDOUT_FILENO) < 0)
			print_error(4, info, 1);
		close(end[1]);
		if (cmd->prev != NULL)
			close(fd_in);
		execute_cmd(info, cmd);
	}
	++i;
}

void	pipe_wait(t_info *info, int *pid, int pipe_cnt)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipe_cnt + 1)
	{
		if (i == pipe_cnt)
			signal(SIGQUIT, sig_quit_with_msg);
		waitpid(pid[i], &status, 0);
	}
	if (WIFEXITED(status) != 0)
		info->error_num = WEXITSTATUS(status);
}
