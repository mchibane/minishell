/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:55:48 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 15:01:51 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "datastructures.h"
#include "parser.h"
#include "lexer.h"

void	redir_cleardata(t_redir *node)
{
	if (node->file)
		free(node->file);
}

void	redir_rm_node(t_redir *node)
{
	redir_cleardata(node);
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node)
		free(node);
}

void	redir_clearlist(t_redir **start)
{
	t_redir	*tmp;

	if (start)
	{
		tmp = *start;
		while (tmp)
		{
			*start = tmp;
			tmp = (*start)->next;
			redir_rm_node(*start);
		}
	}
}
