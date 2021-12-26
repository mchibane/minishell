/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:12:59 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/21 15:44:28 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "datastructures.h"

/*
** HEREDOC FUNC
*/
int		handle_heredocs(t_lexer *token, t_envll **envll);

/*
**	VARIABLE EXPANSION
*/

int		expand_lexer(t_lexer **lexer, t_envll **envll);

t_lexer	*lex_strip_redirs(t_lexer **lexer);

/*
**	COMMAND LIST FUNCTS
*/

t_cmd	*cmd_new_args(t_lexer *args, t_redir *redirs);
void	cmd_clearlist(t_cmd **start);
void	cmd_rm_node(t_cmd *node);
void	cmd_cleardata(t_cmd *node);
t_cmd	*get_cmd_list(char *line, t_envll *envll);
int		set_cmd_args(t_cmd **cmds, t_lexer *lex, int cmd_nbr);
int		set_cmd_redirs(t_cmd **cmds, t_lexer *redirs, int cmd_nbr);
t_cmd	*cmd_setstart(t_cmd *node);

/*
**	REDIR LIST FUNCTS
*/

int		create_redir_list(t_redir **list, t_lexer *redirs);
void	redir_clearlist(t_redir **start);

#endif
