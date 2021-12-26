/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:10:04 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 13:27:28 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

int	set_pwd(t_envll *envll)
{
	char	*pwd;
	char	*key;
	char	*arg;

	(void)envll;
	pwd = getcwd(NULL, 0);
	key = ft_strdup("PWD=");
	arg = ft_strjoin(key, pwd);
	if (!pwd || !key || !arg)
	{
		free_strs(pwd, key, arg);
		return (1);
	}
	export_arg(arg, envll);
	free_strs(pwd, key, arg);
	return (0);
}

int	cd(t_cmd *cmd, t_envll *envll)
{
	int	ac;

	ac = get_ac(cmd->args);
	if (ac < 2)
	{
		print_error("cd: takes only relative or absolute path\n");
		return (1);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		print_error("cd: ");
		print_error(cmd->args[1]);
		print_error(": ");
		print_error(strerror(errno));
		print_error("\n");
		return (1);
	}
	if (set_pwd(envll))
		return (1);
	return (0);
}
