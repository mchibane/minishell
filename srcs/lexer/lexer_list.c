/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:25:04 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/06 15:49:22 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lex_new_node(char *data, int tok_type)
{
	t_lexer	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->data = ft_strdup(data);
	ret->token = tok_type;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	lex_clear_data(t_lexer *node)
{
	if (node->data)
		free(node->data);
}

void	lex_rm_node(t_lexer *node)
{
	lex_clear_data(node);
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node)
		free(node);
}

int	lex_addback(t_lexer **start, t_lexer *node)
{
	t_lexer	*tmp;

	if (node)
	{
		if (!start)
			start = &node;
		if (!(*start))
		{
			*start = node;
			node->prev = NULL;
			node->next = NULL;
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

void	lex_clear_list(t_lexer **start)
{
	t_lexer	*tmp;

	if (start)
	{
		tmp = *start;
		while (tmp)
		{
			*start = tmp;
			tmp = (*start)->next;
			lex_rm_node(*start);
		}
	}
}
