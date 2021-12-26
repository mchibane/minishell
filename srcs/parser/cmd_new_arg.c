/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:07:44 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 16:35:37 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

static int	malloc_size(t_lexer *words)
{
	t_lexer	*tmp;
	int		ret;

	tmp = words;
	ret = 0;
	while (tmp && tmp->token != TOK_PIPE)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

static char	**set_args(t_lexer *words)
{
	t_lexer	*tmp;
	char	**ret;
	int		i;

	tmp = words;
	i = malloc_size(words);
	ret = malloc(sizeof(*ret) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp && tmp->token != TOK_PIPE)
	{
		ret[i] = ft_strdup(tmp->data);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}

t_cmd	*cmd_new_args(t_lexer *args, t_redir *redirs)
{
	t_cmd	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->args = set_args(args);
	ret->name = ret->args[0];
	ret->redirs = redirs;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}
