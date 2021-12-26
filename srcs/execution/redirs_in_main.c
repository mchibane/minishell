/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:15:31 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:32:48 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

int	builtin_main(t_cmd *cmd, t_envll *envll)
{
	int	fd[2];
	int	tmp;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	tmp = exec_redirs(cmd);
	if (tmp != 0)
	{
		g_status = tmp;
		return (g_status);
	}
	g_status = exec_builtin(cmd, envll);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (check_str(cmd->name, EXIT_CMD) && get_ac(cmd->args) <= 2)
		exit_shell(envll, cmd);
	return (g_status);
}
