/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:28:35 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 14:18:59 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_end_index(char *line, int index)
{
	int		i;
	char	*status;

	i = index + 1;
	if (line[i] == '?')
	{
		status = ft_itoa(g_status);
		if (!status)
			return (i);
		i += ft_strlen(status);
		free(status);
		return (i);
	}
	if (line[i] != '_' && !ft_isalpha(line[i]))
		return (i);
	i++;
	while (line && line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}

static char	*set_key(char *line, int start, int end)
{
	char	*ret;

	if (end == -1)
		ret = ft_strdup("?");
	else
		ret = ft_substr(line, start + 1, end - (start + 1));
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*find_value(char *key, t_envll **envll)
{
	char	*ret;
	t_envll	*tmp;

	tmp = *envll;
	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
	{
		ret = ft_itoa(g_status);
		if (!ret)
			return (NULL);
		return (ret);
	}
	while (tmp)
	{
		if (tmp->visible == true
			&& ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
		{
			ret = ft_strdup(tmp->value);
			if (!ret)
				return (NULL);
			return (ret);
		}
		tmp = tmp->next;
	}
	ret = ft_strdup("");
	return (ret);
}

static int	join_strs(char **line, char *value, int start, int end)
{
	char	*to_free;
	char	*s1;
	char	*s2;
	char	*tmp;
	int		ret;

	to_free = *line;
	s1 = ft_substr(*line, 0, start);
	s2 = ft_substr(*line, end, ft_strlen(*line));
	tmp = ft_strjoin(s1, value);
	*line = ft_strjoin(tmp, s2);
	if (!s1 || !s2 || !tmp || !(*line))
	{
		free_strs(s1, s2, tmp);
		*line = to_free;
		return (-1);
	}
	ret = ft_strlen(s1) + ft_strlen(value);
	free_strs(s1, s2, to_free);
	free(tmp);
	return (ret);
}

int	expand_var(char **line, int index, t_envll **envll)
{
	int		i;
	char	*key;
	char	*value;
	int		ret;

	i = set_end_index(*line, index);
	key = set_key(*line, index, i);
	if (!key)
		return (-1);
	if (ft_strlen(key) == 0)
	{
		free(key);
		return (index + 1);
	}
	value = find_value(key, envll);
	if (!value)
	{
		free(key);
		return (-1);
	}
	ret = join_strs(line, value, index, i);
	free(value);
	free(key);
	return (ret);
}
