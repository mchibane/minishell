/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:07:32 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/13 16:38:10 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <limits.h>

static const t_chr_class	g_chr_class[CHAR_MAX] = {
['0'...'9'] = CHR_CLASS_DIGIT,
['a'...'z'] = CHR_CLASS_LETTER,
['A'...'Z'] = CHR_CLASS_LETTER,
['<'] = CHR_CLASS_LARROW,
['>'] = CHR_CLASS_RARROW,
['|'] = CHR_CLASS_PIPE,
['$'] = CHR_CLASS_DOLLAR,
[32] = CHR_CLASS_BLANK,
['\t'] = CHR_CLASS_BLANK,
[34] = CHR_CLASS_QUOTE,
[39] = CHR_CLASS_QUOTE,
['!'] = CHR_CLASS_SYMBOL,
['#'] = CHR_CLASS_SYMBOL,
['%'...'&'] = CHR_CLASS_SYMBOL,
['('...'/'] = CHR_CLASS_SYMBOL,
[':'...';'] = CHR_CLASS_SYMBOL,
['='] = CHR_CLASS_SYMBOL,
['?'...'@'] = CHR_CLASS_SYMBOL,
['['...'`'] = CHR_CLASS_SYMBOL,
['{'] = CHR_CLASS_SYMBOL,
['}'...'~'] = CHR_CLASS_SYMBOL,
[0] = CHR_CLASS_EOL,
['\n'] = CHR_CLASS_EOL
};

static const t_tok_type		g_tok_type[CHAR_MAX] = {
[CHR_CLASS_DIGIT] = TOK_WORD,
[CHR_CLASS_LETTER] = TOK_WORD,
[CHR_CLASS_DOLLAR] = TOK_WORD,
[CHR_CLASS_LARROW] = TOK_REDIR_IN,
[CHR_CLASS_RARROW] = TOK_REDIR_OUT,
[CHR_CLASS_PIPE] = TOK_PIPE,
[CHR_CLASS_QUOTE] = TOK_WORD,
[CHR_CLASS_SYMBOL] = TOK_WORD,
[CHR_CLASS_BLANK] = TOK_BLANK
};

static const int			g_lexer_rules[TOK_MAX][CHAR_MAX] = {
[TOK_WORD] = {
[CHR_CLASS_LETTER] = true,
[CHR_CLASS_DIGIT] = true,
[CHR_CLASS_SYMBOL] = true,
[CHR_CLASS_BLANK] = false,
[CHR_CLASS_LARROW] = false,
[CHR_CLASS_RARROW] = false,
[CHR_CLASS_PIPE] = false,
[CHR_CLASS_DOLLAR] = true,
[CHR_CLASS_QUOTE] = true,
[CHR_CLASS_EOL] = false,
},
[TOK_PIPE] = {
[CHR_CLASS_PIPE] = true,
[CHR_CLASS_LETTER] = false,
[CHR_CLASS_DIGIT] = false,
[CHR_CLASS_SYMBOL] = false,
[CHR_CLASS_BLANK] = false,
[CHR_CLASS_LARROW] = false,
[CHR_CLASS_RARROW] = false,
[CHR_CLASS_DOLLAR] = false,
[CHR_CLASS_QUOTE] = false,
[CHR_CLASS_EOL] = false,
},
[TOK_REDIR_IN] = {
[CHR_CLASS_PIPE] = false,
[CHR_CLASS_LETTER] = false,
[CHR_CLASS_DIGIT] = false,
[CHR_CLASS_SYMBOL] = false,
[CHR_CLASS_BLANK] = false,
[CHR_CLASS_LARROW] = true,
[CHR_CLASS_RARROW] = false,
[CHR_CLASS_DOLLAR] = false,
[CHR_CLASS_QUOTE] = false,
[CHR_CLASS_EOL] = false,
},
[TOK_REDIR_OUT] = {
[CHR_CLASS_PIPE] = false,
[CHR_CLASS_LETTER] = false,
[CHR_CLASS_DIGIT] = false,
[CHR_CLASS_SYMBOL] = false,
[CHR_CLASS_BLANK] = false,
[CHR_CLASS_LARROW] = false,
[CHR_CLASS_RARROW] = true,
[CHR_CLASS_DOLLAR] = false,
[CHR_CLASS_QUOTE] = false,
[CHR_CLASS_EOL] = false,
},
[TOK_BLANK] = {
[CHR_CLASS_PIPE] = false,
[CHR_CLASS_LETTER] = false,
[CHR_CLASS_DIGIT] = false,
[CHR_CLASS_SYMBOL] = false,
[CHR_CLASS_BLANK] = true,
[CHR_CLASS_LARROW] = false,
[CHR_CLASS_RARROW] = false,
[CHR_CLASS_DOLLAR] = false,
[CHR_CLASS_QUOTE] = false,
[CHR_CLASS_EOL] = false,
}
};

int	get_chr_class(int c)
{
	return (g_chr_class[c]);
}

int	get_tok_type(int c)
{
	return (g_tok_type[g_chr_class[c]]);
}

int	get_lex_rule(int c, t_tok_type tok_type)
{
	return (g_lexer_rules[tok_type][g_chr_class[c]]);
}

char	*get_tok_data(char *line, t_tok_type tok)
{
	int		i;
	char	*ret;

	i = 0;
	while (line[i] && get_lex_rule(line[i], tok))
		i++;
	ret = ft_substr(line, 0, i);
	if (!ret)
		return (NULL);
	return (ret);
}

t_lexer	*lex_it(char *line)
{
	int			i;
	t_tok_type	tok_type;
	char		*data;
	t_lexer		*lexer;

	i = 0;
	lexer = NULL;
	data = NULL;
	while (line[i])
	{
		tok_type = get_tok_type(line[i]);
		data = get_tok_data(&line[i], tok_type);
		if (!data)
			return (NULL);
		while (line[i] && get_lex_rule(line[i], tok_type))
			i++;
		if (lex_addback(&lexer, lex_new_node(data, tok_type)))
			return (NULL);
		free(data);
	}
	return (lexer);
}
