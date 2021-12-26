/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:08:10 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/15 18:49:43 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

int	wait_for_it(pid_t *pids, int cmd_nb)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < cmd_nb)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) == 1)
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) == 1)
			g_status = WTERMSIG(status) + 128;
		i++;
	}
	return (0);
}
