/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:51:28 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/18 14:30:37 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

static int	unset_str(char *key, t_envll **envll)
{
	t_envll	*tmp;

	if (!name_is_valid(key))
		return (1);
	tmp = *envll;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
		{
			envll_rm_node(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	unset(t_cmd *cmd, t_envll *envll)
{
	int		ac;
	int		i;
	int		ret;

	ac = get_ac(cmd->args);
	if (ac < 2)
	{
		print_error("unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (unset_str(cmd->args[i], &envll))
		{
			print_error("unset: ");
			print_error(cmd->args[i]);
			print_error(": not a valid identifier\n");
			ret = 1;
		}
		i++;
	}
	return (ret);
}
