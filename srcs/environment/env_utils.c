/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:39:48 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/18 14:11:07 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_split_line(char *line)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(*ret) * 3);
	if (!ret)
		return (NULL);
	i = 0;
	while (line && line[i] && line[i] != '=')
		i++;
	ret[0] = ft_substr(line, 0, i);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_substr(line, i + 1, ft_strlen(line));
	if (!ret[1])
		return (NULL);
	ret[2] = NULL;
	return (ret);
}

static int	get_tab_size(t_envll *envll)
{
	int	i;

	i = 0;
	while (envll)
	{
		envll = envll->next;
		i++;
	}
	return (i);
}

char	**envll_to_tab(t_envll *start)
{
	t_envll	*tmp;
	char	**ret;
	int		i;

	tmp = start;
	i = get_tab_size(tmp);
	ret = malloc(sizeof(*ret) * (i + 1));
	if (!ret)
		return (NULL);
	tmp = start;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->line);
		if (!ret[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	envll_del_data(t_envll *node)
{
	if (node->line)
		free(node->line);
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
}
