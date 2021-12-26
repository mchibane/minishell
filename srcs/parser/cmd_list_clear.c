/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:06:43 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 15:03:20 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "datastructures.h"

void	cmd_cleardata(t_cmd *node)
{
	if (node->args)
		free_tab(node->args);
	if (node->redirs)
		redir_clearlist(&node->redirs);
}

void	cmd_rm_node(t_cmd *node)
{
	cmd_cleardata(node);
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node)
		free(node);
}

void	cmd_clearlist(t_cmd **start)
{
	t_cmd	*tmp;

	if (start)
	{
		tmp = *start;
		while (tmp)
		{
			*start = tmp;
			tmp = (*start)->next;
			cmd_rm_node(*start);
		}
	}
}
