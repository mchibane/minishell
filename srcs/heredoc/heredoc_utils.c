/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:23:36 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:59:46 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"

t_bool	is_heredoc(t_lexer *token)
{
	if (token->token == TOK_REDIR_IN && ft_strlen(token->data) == 2
		&& token->next && token->next->token == TOK_WORD
		&& ((token->prev && token->prev->token == TOK_WORD)
			|| (token->prev == NULL)))
		return (true);
	return (false);
}

void	eof_warning(t_heredoc *hd)
{
	printf("Minishell: warning: here-document at line %lu ",
		*((unsigned long *)get_line(NULL, GET_HISTORY)));
	printf("delimited by end-of-file (wanted `%s')\n", hd->delimiter);
}

static t_bool	check_quote(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

t_heredoc	*init_heredoc(t_heredoc **hd, t_lexer *token)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	*hd = heredoc;
	if (heredoc == NULL)
		return (NULL);
	heredoc->delimiter = ft_strdup(token->next->data);
	heredoc->fd = 0;
	heredoc->path = 0;
	if (check_quote(heredoc->delimiter))
		heredoc->expand = false;
	else
		heredoc->expand = true;
	if (heredoc->expand == false)
		strip_all(&(heredoc->delimiter));
	return (create_tempfile(heredoc));
}
