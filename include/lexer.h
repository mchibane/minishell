/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:21:54 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:09:24 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "datastructures.h"

# define ERR_QUOTE "syntax error : unclosed quotes\n"

# define STOK_WORD "WORD"
# define STOK_REDIR_IN "REDIR_IN"
# define STOK_REDIR_OUT "REDIR_OUT"
# define STOK_PIPE "PIPE"
# define STOK_BLANK "BLANK"

t_lexer	*lex_it(char *line);
t_lexer	*lexer_build(char *line);

int		get_chr_class(int c);
int		get_tok_type(int c);
int		get_lex_rule(int c, t_tok_type tok_type);

int		lex_addback(t_lexer **start, t_lexer *node);
t_lexer	*lex_new_node(char *data, int tok_type);
void	lex_clear_list(t_lexer **start);
void	lex_rm_node(t_lexer *node);
void	lex_clear_data(t_lexer *node);
void	trim_blank(t_lexer **lexer);
t_lexer	*strip_node(t_lexer **start, t_lexer *node);

int		handle_quotes(t_lexer **lexer);
int		group_quotes(t_lexer **lexer);
int		next_quote(char *s, char c);
t_bool	check_lexer_errors(t_lexer **token);
t_lexer	*rewind_lexer(t_lexer *node);

/**/

#endif
