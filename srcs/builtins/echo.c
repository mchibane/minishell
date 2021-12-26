/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:18:55 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 13:31:37 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg && arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_options(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_option(args[i]))
			break ;
		i++;
	}
	return (i);
}

int	echo(char **args)
{
	int		nl;
	int		i;

	args++;
	nl = check_options(args);
	i = nl;
	while (args && args[i])
	{
		if (args[i][0])
		{
			if (write(1, args[i], ft_strlen(args[i])) == -1)
			{
				write_error("echo");
				return (1);
			}
			if (args[i +1])
				write(1, " ", 1);
		}
		i++;
	}
	if (!nl)
		write(1, "\n", 1);
	return (0);
}
