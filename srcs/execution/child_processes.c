/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:20:01 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/17 20:09:29 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include "parser.h"

void	handle_child(t_cmd *cmd, t_envll *envll, pid_t *pids, int **pipefd)
{
	t_cmd	*start;
	int		cmd_nb;
	int		status;

	status = 0;
	handle_sigs(S_CHILD);
	start = cmd_setstart(cmd);
	cmd_nb = get_cmd_nbr(start);
	status = exec_redirs(cmd);
	if (status == 0)
	{
		if (cmd->name)
		{
			if (is_builtin(cmd->name))
				status = exec_builtin(cmd, envll);
			else
				status = exec_bin(cmd->args, envll);
		}
	}
	cmd_clearlist(&start);
	envll_clear(&envll);
	free(pids);
	free_pipefd(pipefd, cmd_nb);
	exit(status);
}

int	fork_it(t_cmd *cmds, t_envll *envll, int cmd_nb, int **pipefd)
{
	t_cmd	*tmp;
	pid_t	*pids;
	int		i;

	tmp = cmds;
	i = 0;
	pids = get_pids(cmd_nb);
	if (!pids)
		return (1);
	while (i < cmd_nb)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			handle_pipefds(pipefd, i, cmd_nb);
			handle_child(tmp, envll, pids, pipefd);
		}
		i++;
		tmp = tmp->next;
	}
	close_pipes(pipefd, cmd_nb);
	wait_for_it(pids, cmd_nb);
	free(pids);
	return (0);
}
