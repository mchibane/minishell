/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:38:49 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/21 15:45:11 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# ifndef TEMP_FILENAME
#  define TEMP_FILENAME "/tmp/minishell_heredoc_"
# endif

typedef enum e_signals
{
	S_MAIN,
	S_FORK,
	S_CHILD
}			t_signals;

typedef enum e_quote
{
	Q_ERROR = -1,
	Q_IN_STR,
	Q_IN_NODE,
	NO_QUOTE,
	Q_NO_MATCH
}			t_quote;

typedef enum e_token
{
	TOK_WORD,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_PIPE,
	TOK_BLANK,
	TOK_MAX
}			t_tok_type;

typedef enum e_chr_class
{
	CHR_CLASS_DIGIT = 1,
	CHR_CLASS_LETTER,
	CHR_CLASS_LARROW,
	CHR_CLASS_RARROW,
	CHR_CLASS_PIPE,
	CHR_CLASS_DOLLAR,
	CHR_CLASS_BLANK,
	CHR_CLASS_QUOTE,
	CHR_CLASS_SYMBOL,
	CHR_CLASS_EOL,
	CHR_CLASS_MAX
}			t_chr_class;

typedef struct s_lexer	t_lexer;
struct s_lexer
{
	char		*data;
	t_tok_type	token;
	t_lexer		*next;
	t_lexer		*prev;
};

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_envll	t_envll;
struct s_envll
{
	char	*key;
	char	*value;
	char	*line;
	t_bool	visible;
	t_envll	*next;
	t_envll	*prev;
};

typedef enum e_redir_type
{
	R_STDIN,
	R_STDOUT,
	R_HERE_DOC,
	R_APPEND
}			t_redir_type;

typedef struct s_redir	t_redir;
struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
	t_redir			*next;
	t_redir			*prev;
};

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	*name;
	char	**args;
	t_redir	*redirs;
	t_cmd	*prev;
	t_cmd	*next;
};

typedef struct s_heredoc
{
	enum e_bool	expand;
	char		*delimiter;
	char		*path;
	int			fd;
}				t_heredoc;

#endif
