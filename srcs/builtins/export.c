/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:23:18 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 13:15:05 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

static int	update_node(char *arg, t_envll *envll)
{
	t_envll	*tmp;
	char	**cmp;
	char	*swap;

	cmp = envp_split_line(arg);
	if (!cmp)
		return (1);
	tmp = envll;
	while (check_str(cmp[0], tmp->key) == 0)
		tmp = tmp->next;
	swap = tmp->value;
	if (equal_in_str(arg))
	{
		tmp->value = ft_strdup(cmp[1]);
		free(swap);
	}
	free_tab(cmp);
	if (!tmp->value)
		return (1);
	tmp->visible = true;
	return (0);
}

static int	export_new(char *arg, t_envll *envll)
{
	t_envll	*node;

	node = envll_newnode(arg);
	if (!node)
		return (1);
	if (!equal_in_str(arg))
		node->visible = false;
	envll_addback(&envll, node);
	return (0);
}

int	export_arg(char *arg, t_envll *envll)
{
	if (!str_is_valid(arg))
		return (1);
	if (arg[0] == 0)
		return (0);
	if (node_exists(arg, envll))
		return (update_node(arg, envll));
	else
		return (export_new(arg, envll));
	return (0);
}

static int	no_args(t_envll *envll)
{
	t_envll	*tmp;

	tmp = envll;
	while (tmp)
	{
		if (printf("export %s", tmp->key) < 0)
		{
			write_error("env");
			return (1);
		}
		if (tmp->visible)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	return (0);
}

int	export(t_cmd *cmd, t_envll *envll)
{
	int	ac;
	int	i;
	int	ret;

	ac = get_ac(cmd->args);
	if (ac == 1)
		return (no_args(envll));
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (export_arg(cmd->args[i], envll))
		{
			print_error("export: ");
			print_error(cmd->args[i]);
			print_error(": not a valid identifier\n");
			ret = 1;
		}
		i++;
	}
	return (ret);
}
