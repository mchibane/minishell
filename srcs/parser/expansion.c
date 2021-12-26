/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:07:23 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 17:59:17 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

int	expand_lexer(t_lexer **lexer, t_envll **envll)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (tmp->token == TOK_REDIR_IN && ft_strlen(tmp->data) == 2)
		{
			tmp = tmp->next;
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
			continue ;
		}
		if (expand(&tmp->data, envll) == -1)
			return (-1);
		if (strip_all(&tmp->data) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
