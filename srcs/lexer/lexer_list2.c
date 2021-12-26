/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:38:26 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:00:13 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	trim_blank(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*del;

	tmp = *lexer;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		if (del->token == TOK_BLANK && del->prev == NULL)
		{
			*lexer = tmp;
		}
		if (del->token == TOK_BLANK)
			lex_rm_node(del);
	}
}

t_lexer	*strip_node(t_lexer **start, t_lexer *node)
{
	if (node->prev == NULL)
		*start = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lexer	*rewind_lexer(t_lexer *node)
{
	while (node->prev)
		node = node->prev;
	return (node);
}
