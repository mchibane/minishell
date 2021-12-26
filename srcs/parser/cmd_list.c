/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:35:33 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 18:16:39 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

int	cmd_addback(t_cmd **start, t_cmd *node)
{
	t_cmd	*tmp;

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

static void	set_args_ptr(t_lexer **args)
{
	t_lexer	*tmp;

	tmp = *args;
	if (tmp && tmp->token == TOK_PIPE)
	{
		tmp = tmp->next;
		*args = tmp;
		return ;
	}
	while (tmp && tmp->token != TOK_PIPE)
		tmp = tmp->next;
	if (tmp)
		tmp = tmp->next;
	*args = tmp;
}

static void	set_redir_ptr(t_lexer **redirs)
{
	t_lexer	*tmp;

	tmp = *redirs;
	if (tmp && tmp->token == TOK_PIPE)
	{
		tmp = tmp->next;
		*redirs = tmp;
		return ;
	}
	while (tmp && tmp->token != TOK_PIPE)
		tmp = tmp->next;
	if (tmp)
		tmp = tmp->next;
	*redirs = tmp;
}

int	set_cmd_args(t_cmd **cmds, t_lexer *lex, int cmd_nbr)
{
	t_lexer	*args_ptr;

	args_ptr = lex;
	while (cmd_nbr > 0)
	{
		if (cmd_addback(cmds, cmd_new_args(args_ptr, NULL)))
			return (1);
		set_args_ptr(&args_ptr);
		cmd_nbr--;
	}
	return (0);
}

int	set_cmd_redirs(t_cmd **cmds, t_lexer *redirs, int cmd_nbr)
{
	t_lexer	*redirs_ptr;
	t_redir	*cmd_redirs;
	t_cmd	*tmp;

	redirs_ptr = redirs;
	cmd_redirs = NULL;
	tmp = *cmds;
	while (cmd_nbr > 0)
	{
		if (create_redir_list(&cmd_redirs, redirs_ptr))
			return (1);
		tmp->redirs = cmd_redirs;
		cmd_redirs = NULL;
		set_redir_ptr(&redirs_ptr);
		cmd_nbr--;
		tmp = tmp->next;
	}
	return (0);
}
