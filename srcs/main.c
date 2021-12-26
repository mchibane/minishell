/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:19:58 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 13:05:10 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int	g_status = 0;

void	exit_shell(t_envll *envll, t_cmd *cmd)
{
	unlink_hd(cmd);
	if (cmd)
		cmd_clearlist(&cmd);
	envll_clear(&envll);
	printf ("exit\n");
	rl_clear_history();
	rl_replace_line("exit", 0);
	rl_redisplay();
	exit(g_status);
}

static void	exec_line(char *line, t_envll *envll)
{
	t_cmd	*cmds;

	cmds = get_cmd_list(line, envll);
	if (!cmds)
		return ;
	if (get_cmd_nbr(cmds) == 1 && cmds->name && is_builtin(cmds->name))
	{
		builtin_main(cmds, envll);
	}
	else
		execute(cmds, envll);
	unlink_hd(cmds);
	cmd_clearlist(&cmds);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_envll	*envll;

	if (ac != 1)
		return (0);
	(void)av;
	handle_sigs(S_MAIN);
	if (!envp[0])
		return (-1);
	envll = envp_to_llist(envp);
	while (1)
	{
		line = (char *)get_line("Minishell > ", GET_LINE);
		if (!line)
			exit_shell(envll, NULL);
		if (line && *line != 0)
		{
			add_history(line);
			exec_line(line, envll);
		}
		free(line);
	}
	return (0);
}
