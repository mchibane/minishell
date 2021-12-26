/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:51:49 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/06 16:36:31 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*create_str(t_lexer *first, t_lexer *current)
{
	char	*ret;
	char	*tmp;
	t_lexer	*l_tmp;

	ret = NULL;
	tmp = NULL;
	l_tmp = first;
	while (l_tmp != current->next)
	{
		tmp = ret;
		ret = ft_strjoin(tmp, l_tmp->data);
		if (!ret)
			return (NULL);
		free(tmp);
		l_tmp = l_tmp->next;
	}
	return (ret);
}

static void	clear_between(t_lexer *first, t_lexer *current)
{
	t_lexer	*tmp;

	tmp = first;
	while (tmp != current)
	{
		first = tmp;
		tmp = first->next;
		lex_clear_data(first);
		free(first);
	}
	first = tmp;
	tmp = first->next;
	lex_clear_data(first);
	free(first);
}

static int	join_nodes(t_lexer *first, t_lexer *current, t_lexer **head)
{
	char	*str;
	t_lexer	*new;

	str = create_str(first, current);
	new = lex_new_node(str, TOK_WORD);
	if (!new)
		return (1);
	new->prev = first->prev;
	new->next = current->next;
	if (new->prev)
		new->prev->next = new;
	else
		*head = new;
	if (new->next)
		new->next->prev = new;
	clear_between(first, current);
	first = new;
	current = new;
	free(str);
	return (0);
}

static int	find_next_quote(char *str, t_lexer *lex, char quote, t_lexer **head)
{
	t_lexer	*tmp;

	str++;
	while (str && *str)
	{
		if (*str == quote)
			return (Q_IN_STR);
		str++;
	}
	tmp = lex->next;
	while (tmp)
	{
		str = tmp->data;
		while (str && *str)
		{
			if (*str++ == quote)
			{
				if (join_nodes(lex, tmp, head))
					return (Q_ERROR);
				return (Q_IN_NODE);
			}
		}
		tmp = tmp->next;
	}
	return (Q_NO_MATCH);
}

int	handle_quotes(t_lexer **lexer)
{
	t_lexer	*tmp;
	char	*str;
	int		quote;

	tmp = *lexer;
	while (tmp)
	{
		str = tmp->data;
		while (*str)
		{
			if (get_chr_class(*str) == CHR_CLASS_QUOTE)
			{
				quote = find_next_quote(str, tmp, *str, lexer);
				if (quote == Q_IN_STR)
					str += next_quote(str, *str);
				else
					return (quote);
			}
			str++;
		}
		tmp = tmp->next;
	}
	return (NO_QUOTE);
}
