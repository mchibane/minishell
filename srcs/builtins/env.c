/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:20:33 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/21 13:45:08 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

static int	print_env(t_envll *start)
{
	t_envll	*tmp;

	tmp = start;
	while (tmp)
	{
		if (tmp->visible == true && tmp->value)
		{
			if (printf("%s=%s\n", tmp->key, tmp->value) < 0)
			{
				write_error("env");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env(t_cmd *cmd, t_envll *envll)
{
	int	ac;

	ac = get_ac(cmd->args);
	if (ac != 1)
	{
		print_error("error: env takes no arguments or options\n");
		return (1);
	}
	if (print_env(envll))
		return (1);
	return (0);
}
