/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:11:27 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:30:34 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include "parser.h"

int	exec_builtin(t_cmd *cmd, t_envll *envll)
{
	int	ret;

	if (check_str(cmd->args[0], PWD_CMD))
		ret = pwd_cmd();
	if (check_str(cmd->args[0], ECHO_CMD))
		ret = echo(cmd->args);
	if (check_str(cmd->args[0], EXIT_CMD))
		ret = msh_exit(cmd);
	if (check_str(cmd->args[0], ENV_CMD))
		ret = env(cmd, envll);
	if (check_str(cmd->args[0], UNSET_CMD))
		ret = unset(cmd, envll);
	if (check_str(cmd->args[0], EXPORT_CMD))
		ret = export(cmd, envll);
	if (check_str(cmd->args[0], CD_CMD))
		ret = cd(cmd, envll);
	return (ret);
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_bin(char **args, t_envll *envll)
{
	char	*cmd;
	char	**envp;

	if (check_spaces(args[0]))
		return (0);
	envp = envll_to_tab(envll);
	if (!envp)
		return (1);
	cmd = get_path(args, envp);
	if (!cmd)
	{
		free_tab(envp);
		print_error(args[0]);
		print_error(": command not found\n");
		return (127);
	}
	execve(cmd, args, envp);
	perror(args[0]);
	free_tab(envp);
	free(cmd);
	return (127);
}

pid_t	*get_pids(int cmd_nb)
{
	pid_t	*ret;

	ret = malloc(sizeof(*ret) * cmd_nb);
	if (!ret)
		return (NULL);
	return (ret);
}

void	execute(t_cmd *cmds, t_envll *envll)
{
	int	**pipefd;
	int	cmd_nbr;

	cmd_nbr = get_cmd_nbr(cmds);
	pipefd = NULL;
	if (cmd_nbr > 1)
	{
		pipefd = get_pipefds(cmd_nbr);
		if (!pipefd)
			return ;
	}
	handle_sigs(S_FORK);
	fork_it(cmds, envll, cmd_nbr, pipefd);
	handle_sigs(S_MAIN);
	free_pipefd(pipefd, cmd_nbr);
}
