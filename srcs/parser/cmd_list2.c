/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:58:40 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 13:50:34 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include "lexer.h"
#include "parser.h"

static int	get_cmd_nb(t_lexer *lexer)
{
	int		ret;
	t_lexer	*tmp;

	ret = 0;
	tmp = lexer;
	while (tmp)
	{
		if (!tmp->next || tmp->next->token == TOK_PIPE)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

static t_cmd	*create_cmds(t_lexer **lex, int cmd_nbr)
{
	t_cmd	*cmds;
	t_lexer	*lex_redirs;

	cmds = NULL;
	lex_redirs = lex_strip_redirs(lex);
	if (set_cmd_args(&cmds, *lex, cmd_nbr))
		return (NULL);
	if (set_cmd_redirs(&cmds, lex_redirs, cmd_nbr))
		return (NULL);
	lex_clear_list(&lex_redirs);
	return (cmds);
}

t_cmd	*get_cmd_list(char *line, t_envll *envll)
{
	t_cmd	*cmds;
	t_lexer	*lex;
	int		cmd_nbr;

	lex = lexer_build(line);
	if (!lex || !check_lexer_errors(&lex) || expand_lexer(&lex, &envll) == -1)
	{
		g_status = 2;
		return (NULL);
	}
	if (handle_heredocs(lex, &envll) < 0)
	{
		lex_clear_list(&lex);
		return (NULL);
	}
	cmd_nbr = get_cmd_nb(lex);
	cmds = create_cmds(&lex, cmd_nbr);
	lex_clear_list(&lex);
	return (cmds);
}

t_cmd	*cmd_setstart(t_cmd *node)
{
	t_cmd	*ret;

	ret = node;
	while (ret->prev)
		ret = ret->prev;
	return (ret);
}
