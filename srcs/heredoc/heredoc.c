/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:53:19 by rballage          #+#    #+#             */
/*   Updated: 2021/12/22 18:27:26 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "minishell.h"
#include "lexer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char	*heredoc_expand(char **line, t_bool expand, t_envll **envll)
{
	if (expand == true)
	{
		if (expand_all(line, envll) < 0)
		{
			ft_strdel(line);
			exit(1);
		}
	}
	return (*line);
}

static void	create_heredoc(t_heredoc *hd, t_envll **envll)
{
	char	*line;

	line = NULL;
	while (hd)
	{
		line = readline("> ");
		if (line == NULL)
			eof_warning(hd);
		if (line != NULL && !check_str(line, hd->delimiter))
			put_line_to_fd(hd->fd, heredoc_expand(&line, hd->expand, envll));
		else
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_strdel(&(hd->delimiter));
	ft_strdel(&(hd->path));
	free(hd);
	envll_clear(envll);
}

static void	heredoc_child(t_heredoc *hd, t_envll **envll, t_lexer **lex)
{
	t_lexer	*node;

	node = rewind_lexer(*lex);
	signal(SIGINT, SIG_DFL);
	create_heredoc(hd, envll);
	lex_clear_list(&node);
	exit(0);
}

static int	exec_heredoc(t_heredoc *hd, t_envll **envll, t_lexer **lex)
{
	int	id;
	int	status;

	status = 0;
	id = fork();
	if (id == 0)
		heredoc_child(hd, envll, lex);
	else if (id != -1)
	{
		handle_sigs(S_FORK);
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			g_status = WTERMSIG(status) + 128;
		}
		return (g_status);
	}
	return (-1);
}

int	handle_heredocs(t_lexer *token, t_envll **envll)
{
	t_heredoc	*heredoc;

	heredoc = NULL;
	while (token)
	{
		if (is_heredoc(token))
		{
			if (exec_heredoc(init_heredoc(&heredoc, token), envll, &token) == 0)
			{
				handle_sigs(S_MAIN);
				heredoc_clear(heredoc, token);
			}
			else
			{
				heredoc_clear(heredoc, token);
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}
