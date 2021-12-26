/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:59:38 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:26:20 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_path_line(char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], PATH_STR, 4) == 0)
			break ;
		i++;
	}
	ret = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (ret);
}

char	**set_path_tab(char *path_line)
{
	char	*tmp;
	int		i;
	char	**ret;

	ret = ft_split(path_line, ':');
	i = 0;
	while (ret && ret[i])
	{
		tmp = ret[i];
		ret[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (ret);
}

char	**parse_path(char **envp)
{
	char	*path_line;
	char	**ret;

	path_line = set_path_line(envp);
	if (!path_line)
		return (NULL);
	ret = set_path_tab(path_line);
	free(path_line);
	return (ret);
}

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
