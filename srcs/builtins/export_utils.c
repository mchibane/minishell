/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:00:50 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/18 15:06:29 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

int	str_is_valid(char *str)
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
		if (str[i] == '=')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '=' && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	equal_in_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	node_exists(char *arg, t_envll *envll)
{
	t_envll	*tmp;
	int		i;
	char	*cmp;

	tmp = envll;
	i = equal_in_str(arg);
	if (i == 0)
		i = ft_strlen(arg);
	cmp = ft_substr(arg, 0, i);
	if (!cmp)
		return (0);
	while (tmp)
	{
		if (check_str(cmp, tmp->key))
		{
			free(cmp);
			return (1);
		}
		tmp = tmp->next;
	}
	free(cmp);
	return (0);
}
