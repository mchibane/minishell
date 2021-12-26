/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:46:29 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/20 15:57:53 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	strip_all(char **line)
{
	int	i;

	i = 0;
	while (*line && (*line)[i])
	{
		if (get_chr_class((*line)[i]) == CHR_CLASS_QUOTE)
		{
			i = strip_quotes(line, i);
			if (i < 0)
				return (-1);
			if ((unsigned int)i > ft_strlen(*line))
				break ;
			continue ;
		}
		i++;
	}
	return (0);
}

static int	skip_squotes(char *line)
{
	int	i;

	i = 1;
	while (line && line[i] != *line)
		i++;
	return (i);
}

static int	in_quotes(char **line, int i, t_envll **envll)
{
	if ((*line)[i] == 39)
		i += skip_squotes(*line + i);
	else
	{
		i++;
		while ((*line)[i] != 34)
		{
			if ((*line)[i] == '$')
			{
				i = expand_var(line, i, envll);
				if (i < 0)
					return (-1);
				if ((unsigned int)i > ft_strlen(*line))
					break ;
				continue ;
			}
			i++;
		}
	}
	return (i);
}

int	expand(char **line, t_envll **envll)
{
	int	i;

	i = 0;
	while (*line && (*line)[i])
	{
		if (get_chr_class((*line)[i]) == CHR_CLASS_QUOTE)
		{
			i = in_quotes(line, i, envll);
			if (i < 0)
				return (-1);
		}
		if (line && (*line)[i] && (*line)[i] == '$')
		{
			i = expand_var(line, i, envll);
			if (i < 0)
				return (-1);
			if ((unsigned int)i > ft_strlen(*line))
				break ;
			continue ;
		}
		i++;
	}
	return (0);
}

int	expand_all(char **line, t_envll **envll)
{
	int	i;

	i = 0;
	while (*line && (*line)[i])
	{
		if (line && (*line)[i] && (*line)[i] == '$')
		{
			i = expand_var(line, i, envll);
			if (i < 0)
				return (-1);
			if ((unsigned int)i > ft_strlen(*line))
				break ;
			continue ;
		}
		i++;
	}
	return (0);
}
