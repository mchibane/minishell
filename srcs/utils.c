/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:57:42 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:26:06 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_path(char **args, char **envp)
{
	char	*ret;
	int		i;
	char	**paths;

	i = 0;
	ret = NULL;
	if (check_slash(args[0]))
		return (ft_strdup(args[0]));
	paths = parse_path(envp);
	while (paths && paths[i])
	{
		ret = ft_strjoin(paths[i], args[0]);
		if (access(ret, X_OK) == 0)
		{
			free_tab(paths);
			return (ret);
		}
		free(ret);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	ft_strdel(char **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	put_line_to_fd(int fd, char *line)
{
	if (line && *line)
	{
		if (write(fd, line, ft_strlen(line)) < 0)
		{
			ft_strdel(&line);
			exit(1);
		}
	}
	if (write(fd, "\n", 1) < 0)
	{
		ft_strdel(&line);
		exit(1);
	}
}
