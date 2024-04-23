/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:44:43 by jiryu             #+#    #+#             */
/*   Updated: 2023/09/28 19:20:29 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (EXIT_SUCCESS);
}

static void	sigint_handler(int sig)
{
	sig = 0;
	if (g_in_heredoc == 0)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (g_in_heredoc == 1)
	{
		g_in_heredoc = 0;
		rl_replace_line("", 0);
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_quit_no_msg(int signal)
{
	signal = 0;
}

void	sig_quit_with_msg(int signal)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(signal, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
