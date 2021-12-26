/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:43:01 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 16:39:33 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	next_quote(char *s, char c)
{
	int	i;

	i = 1;
	while (s && s[i] != c)
		i++;
	return (i);
}

int	group_quotes(t_lexer **lexer)
{
	int	ret;

	ret = handle_quotes(lexer);
	if (ret == Q_ERROR || ret == Q_NO_MATCH)
	{
		if (ret == Q_NO_MATCH)
			print_error(ERR_QUOTE);
		return (Q_ERROR);
	}
	while (ret == Q_IN_NODE)
	{
		ret = handle_quotes(lexer);
		if (ret == Q_ERROR || ret == Q_NO_MATCH)
		{
			if (ret == Q_NO_MATCH)
				print_error(ERR_QUOTE);
			return (Q_ERROR);
		}
	}
	return (ret);
}

t_lexer	*lexer_build(char *line)
{
	t_lexer	*ret;

	ret = lex_it(line);
	if (!ret)
		return (NULL);
	if (group_quotes(&ret) == Q_ERROR)
	{
		lex_clear_list(&ret);
		return (NULL);
	}
	trim_blank(&ret);
	return (ret);
}
