/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:13:22 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 14:48:13 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

t_lexer	*lex_strip_redirs(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*ret;
	t_lexer	*i;

	i = *lexer;
	ret = NULL;
	while (i)
	{
		if (i->token == TOK_REDIR_IN || i->token == TOK_REDIR_OUT)
		{
			tmp = i;
			i = i->next;
			lex_addback(&ret, strip_node(lexer, tmp));
			tmp = i;
			i = i->next;
			lex_addback(&ret, strip_node(lexer, tmp));
			continue ;
		}
		if (i->token == TOK_PIPE)
		{
			lex_addback(&ret, lex_new_node("|", TOK_PIPE));
		}
		i = i->next;
	}
	return (ret);
}

t_redir_type	get_redir_type(t_lexer	*redir)
{
	if (redir->token == TOK_REDIR_IN)
	{
		if (ft_strlen(redir->data) == 2)
			return (R_HERE_DOC);
		else
			return (R_STDIN);
	}
	else
	{
		if (ft_strlen(redir->data) == 2)
			return (R_APPEND);
		else
			return (R_STDOUT);
	}
}

int	redir_addback(t_redir **start, t_redir *node)
{
	t_redir	*tmp;

	if (node)
	{
		if (!start)
			start = &node;
		if (!(*start))
		{
			*start = node;
			node->next = NULL;
			node->prev = NULL;
			return (0);
		}
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->next = NULL;
		node->prev = tmp;
		return (0);
	}
	return (1);
}

t_redir	*redir_newnode(t_lexer *redirs)
{
	t_redir	*ret;
	t_lexer	*tmp;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	tmp = redirs;
	ret->fd = 0;
	ret->type = get_redir_type(tmp);
	tmp = tmp->next;
	ret->file = ft_strdup(tmp->data);
	return (ret);
}

int	create_redir_list(t_redir **list, t_lexer *redirs)
{
	t_lexer	*tmp;

	tmp = redirs;
	if (!tmp || tmp->token == TOK_PIPE)
	{
		*list = NULL;
		return (0);
	}
	while (tmp && tmp->token != TOK_PIPE)
	{
		if (redir_addback(list, redir_newnode(tmp)))
		{
			*list = NULL;
			return (1);
		}
		tmp = tmp->next->next;
	}
	return (0);
}
