/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:40:04 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:30:39 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include <limits.h>

static int	check_error(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	if (ft_strlen(arg) > 19)
		return (1);
	if (ft_strlen(arg) == 19
		&& ft_strncmp(arg, "9223372036854775807", ft_strlen(arg)) > 0)
		return (1);
	return (0);
}

int	msh_exit(t_cmd *cmd)
{
	int			ac;
	long int	value;

	ac = get_ac(cmd->args);
	if (ac > 2)
	{
		print_error("exit: too many arguments\n");
		return (1);
	}
	if (ac > 1 && check_error(cmd->args[1]))
	{
		print_error("exit: ");
		print_error(cmd->args[1]);
		print_error(": numeric argument required\n");
		return (2);
	}
	if (ac == 1)
		exit(g_status);
	else
		value = ft_atol(cmd->args[1]);
	return ((unsigned char)value);
}
