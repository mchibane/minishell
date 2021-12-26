/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:24:47 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:34:49 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2)
		&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (true);
	return (false);
}

int	is_builtin(char *cmd)
{
	if (check_str(cmd, ECHO_CMD)
		|| check_str(cmd, PWD_CMD)
		|| check_str(cmd, CD_CMD)
		|| check_str(cmd, UNSET_CMD)
		|| check_str(cmd, EXIT_CMD)
		|| check_str(cmd, EXPORT_CMD)
		|| check_str(cmd, ENV_CMD))
		return (true);
	return (false);
}

int	get_ac(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	name_is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == 0)
		return (1);
	if (!str || (ft_isalpha(str[i]) == 0 && str[i] != '_'))
		return (0);
	i++;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	write_error(char *s)
{
	print_error(s);
	print_error(": write error\n");
}
