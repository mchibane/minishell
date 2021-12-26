/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:59:35 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/17 14:13:30 by rballage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_bool	validate_redir(t_lexer *token)
{
	int	len;

	len = ft_strlen(token->data);
	if (len == 1 || len == 2)
	{
		if (token->next && token->next->token == TOK_WORD)
			return (true);
	}
	return (false);
}

static t_bool	validate_pipe(t_lexer *token)
{
	if (ft_strlen(token->data) == 1)
	{
		if (token->next && token->next->token != TOK_PIPE
			&& token->prev && token->prev->token != TOK_PIPE)
			return (true);
	}
	return (false);
}

static t_bool	validate_lexer(t_lexer *token)
{
	while (token)
	{
		if (token->token == TOK_PIPE && !validate_pipe(token))
			return (false);
		else if ((token->token == TOK_REDIR_OUT || token->token == TOK_REDIR_IN)
			&& !validate_redir(token))
			return (false);
		token = token->next;
	}
	return (true);
}

t_bool	check_lexer_errors(t_lexer **token)
{
	if (token && *token)
	{
		if (!validate_lexer(*token))
		{
			lex_clear_list(token);
			print_error("Minishell: syntax error\n");
			return (false);
		}
		return (true);
	}
	return (false);
}
