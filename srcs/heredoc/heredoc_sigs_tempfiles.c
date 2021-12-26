/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:41:28 by rballage          #+#    #+#             */
/*   Updated: 2021/12/21 15:39:40 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include "parser.h"
#include "lexer.h"

void	*get_line(const char *append, int instruction)
{
	static unsigned long	line_read;

	if (instruction == GET_HISTORY)
		return (&line_read);
	line_read++;
	return ((void *)(readline(append)));
}

void	heredoc_sigs_handling(void)
{
	signal(SIGINT, SIG_DFL);
}

char	*get_tempfile_name(int tempfile_nb)
{
	const char	*tempfile_start = TEMP_FILENAME;
	char		*num;
	char		*tempfile_name;

	num = ft_itoa(tempfile_nb);
	tempfile_name = ft_strjoin(tempfile_start, num);
	ft_strdel(&num);
	return (tempfile_name);
}

t_heredoc	*create_tempfile(t_heredoc *heredoc)
{
	static int	tmpfile_nb = 0;

	heredoc->fd = 0;
	while (!heredoc->path || heredoc->fd <= 0)
	{
		ft_strdel(&(heredoc->path));
		heredoc->path = get_tempfile_name(tmpfile_nb++);
		if (!heredoc->path)
			break ;
		else
		{
			heredoc->fd = open(heredoc->path, O_CREAT
					| O_EXCL | O_RDWR | O_APPEND, 0666);
			if (heredoc->fd > 0)
				return (heredoc);
		}
	}
	ft_strdel(&(heredoc->path));
	ft_strdel(&(heredoc->delimiter));
	free(heredoc);
	return (NULL);
}

void	heredoc_clear(t_heredoc *heredoc, t_lexer *token)
{
	ft_strdel(&(token->next->data));
	if (heredoc)
	{
		close(heredoc->fd);
		token->next->data = ft_strdup(heredoc->path);
		free(heredoc->path);
		if (heredoc->delimiter)
			free(heredoc->delimiter);
		free(heredoc);
	}
}
