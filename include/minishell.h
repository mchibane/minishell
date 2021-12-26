/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchibane <mchibane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:18:35 by mchibane          #+#    #+#             */
/*   Updated: 2021/12/22 15:09:08 by mchibane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "datastructures.h"

extern int	g_status;

/*
**	STRING LITTERALS
*/

/*
**		COMMAND NAMES
*/

# define ECHO_CMD "echo"
# define PWD_CMD "pwd"
# define CD_CMD	"cd"
# define EXIT_CMD "exit"
# define UNSET_CMD "unset"
# define EXPORT_CMD "export"
# define ENV_CMD "env"

# define PATH_STR "PATH"

# define GET_LINE 0
# define GET_HISTORY 1

/*
**		ERROR MESSAGES
*/

char		**parse_path(char **envp);
void		free_tab(char **tab);
char		*get_path(char **args, char **paths);
void		handle_sigs(t_signals mode);
int			tab_len(char **tab);
int			check_str(char *s1, char *s2);
int			check_slash(char *cmd);
char		*check_cmd(char *cmd);

/*
**	PRINT ERROR FUNCTS
*/

void		print_error(char *s);
void		print_eredir(char *file);

/*
**	PRINT FUNCTIONS FOR DEBUGG
*/

void		print_envp(char **envp);
void		print_envll(t_envll *start);
void		print_cmd_list(t_cmd *list);
void		print_lexer(t_lexer *lexer);
void		print_tok_type(int c);
void		print_single_cmd(t_cmd *node);

/*
** ENVIRONMENT LINKED LIST FUNCTS
*/

t_envll		*envp_to_llist(char **envp);
char		**envll_to_tab(t_envll *start);
t_envll		*envll_newnode(char *line);
void		envll_rm_node(t_envll *node);
int			envll_addback(t_envll **start, t_envll *node);
void		envll_clear(t_envll	**start);
char		**envp_split_line(char *line);
void		envll_del_data(t_envll *node);

/*
** BUILT-INS
*/

int			pwd_cmd(void);
int			echo(char **args);
int			is_builtin(char *cmd);
int			msh_exit(t_cmd *cmd);
void		exit_shell(t_envll *envll, t_cmd *cmd);
int			get_ac(char **args);
int			env(t_cmd *cmd, t_envll *envll);
int			unset(t_cmd *cmd, t_envll *envll);
int			name_is_valid(char *str);
int			export(t_cmd *cmd, t_envll *envll);
int			str_is_valid(char *str);
int			equal_in_str(char *str);
int			node_exists(char *arg, t_envll *envll);
int			cd(t_cmd *cmd, t_envll *envll);
void		write_error(char *s);
int			export_arg(char *arg, t_envll *envll);

/*
**	EXPANSION FUNCTS
*/

int			expand_var(char **line, int index, t_envll **envll);
int			strip_quotes(char **line, int index);
void		free_strs(char *s1, char *s2, char *s3);
int			expand(char **line, t_envll **envll);
int			strip_all(char **line);
int			expand_all(char **line, t_envll **envll);

/*
**	EXECUTION FUNTCTS
*/

int			exec_builtin(t_cmd *cmd, t_envll *envll);
int			exec_bin(char **args, t_envll *envll);
void		execute(t_cmd *cmds, t_envll *envll);
int			get_cmd_nbr(t_cmd *cmds);
int			fork_it(t_cmd *cmds, t_envll *envll, int cmd_nb, int **pipefd);
pid_t		*get_pids(int cmd_nb);
int			exec_redirs(t_cmd *cmd);
int			builtin_main(t_cmd *cmd, t_envll *envll);

/*
**	PIPES HANDELING FUNCTS
*/

int			**get_pipefds(int cmd_nb);
void		handle_pipefds(int **pipefd, int index, int cmd_nb);
void		free_pipefd(int **pipefd, int cmd_nb);
void		close_pipes(int **pipefd, int cmd_nb);

/*
**	WAIT FUNCTS
*/

int			wait_for_it(pid_t *pids, int cmd_nb);

/*
**	HEREDOCS FUNCTS
*/

void		*get_line(const char *append, int instruction);
void		heredoc_interupt(int *interupt_ptr, int set);
void		heredoc_sigs_action(int signum);
t_bool		is_heredoc(t_lexer *token);
t_bool		str_is_equal(const char *s1, const char *s2);
void		rem_quotes(char *str);
void		put_line_to_fd(int fd, char *line);
void		eof_warning(t_heredoc *hd);
void		*get_line(const char *append, int instruction);
char		*get_tempfile_name(int tempfile_nb);
t_heredoc	*create_tempfile(t_heredoc *heredoc);
void		ft_strdel(char **ap);
void		heredoc_clear(t_heredoc *heredoc, t_lexer *token);
t_heredoc	*init_heredoc(t_heredoc **hd, t_lexer *token);
void		unlink_hd(t_cmd *cmds);

#endif
