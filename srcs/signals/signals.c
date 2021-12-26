/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:24 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/18 17:51:48 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 128 + signum;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	main_fork(int signum)
{
	if (signum == SIGQUIT)
		print_error("Quit (core dumped)\n");
	if (signum == SIGINT)
		write(1, "\n", 1);
}

void	handle_sigs(t_signals mode)
{
	if (mode == S_MAIN)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == S_FORK)
	{
		signal(SIGINT, &main_fork);
		signal(SIGQUIT, &main_fork);
	}
	if (mode == S_CHILD)
		signal(SIGQUIT, SIG_DFL);
}
