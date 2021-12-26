/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:12:24 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/09 14:37:17 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static int	next_quote_index(char *line, int index)
{
	int	i;

	i = index + 1;
	while (line && line[i] && line[i] != line[index])
		i++;
	return (i);
}

static int	join_strs(char	**line, int index)
{
	char	*to_free;
	char	*s1;
	char	*s2;

	to_free = *line;
	s1 = ft_substr(*line, 0, index);
	s2 = ft_substr(*line, index + 1, ft_strlen(*line));
	*line = ft_strjoin(s1, s2);
	if (!s1 || !s2 || !(*line))
	{
		*line = to_free;
		free_strs(s1, s2, NULL);
		return (-1);
	}
	free_strs(s1, s2, to_free);
	return (0);
}

int	strip_quotes(char **line, int index)
{
	int		i;

	i = next_quote_index(*line, index);
	if (join_strs(line, index) == -1)
		return (-1);
	i--;
	if (i < 0)
		i = 0;
	if (join_strs(line, i) == -1)
		return (-1);
	return (i);
}
