NAME				=	minishell
LIBFT				=	libftprintf.a
HEADER				=	minishell.h

SRCS_DIR			=	srcs/
OBJS_DIR			=	objs/
INC_DIR				=	include/
LIBFT_DIR			=	libft/
LIBEXT_DIR			=	externals/

PARSER_DIR			=	parser/
SIG_DIR				=	signals/
BUILTINS_DIR		=	builtins/
ENV_DIR				=	environment/
LEX_DIR				=	lexer/
EXPAND_DIR			=	expansion/
HEREDOC_DIR			=	heredoc/
EXEC_DIR			=	execution/

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf
INCLUDE				=	$(LIBEXTINC) -I$(INC_DIR) -I$(LIBFT_DIR)$(INC_DIR) -I$(LIBFT_DIR)$(LIBFT_DIR)

SRCS				=	$(SRCS_DIR)main.c\
						$(SRCS_DIR)utils.c\
						$(SRCS_DIR)error.c\
						\
						$(SRCS_DIR)$(ENV_DIR)environment.c\
						$(SRCS_DIR)$(ENV_DIR)env_utils.c\
						\
						$(SRCS_DIR)$(PARSER_DIR)cmd_list_clear.c\
						$(SRCS_DIR)$(PARSER_DIR)cmd_list.c\
						$(SRCS_DIR)$(PARSER_DIR)cmd_list2.c\
						$(SRCS_DIR)$(PARSER_DIR)cmd_new_arg.c\
						$(SRCS_DIR)$(PARSER_DIR)expansion.c\
						$(SRCS_DIR)$(PARSER_DIR)parser_error.c\
						$(SRCS_DIR)$(PARSER_DIR)redir_list_clear.c\
						$(SRCS_DIR)$(PARSER_DIR)redir_list.c\
						$(SRCS_DIR)$(PARSER_DIR)simple_parsing.c\
						\
						$(SRCS_DIR)$(SIG_DIR)signals.c\
						\
						$(SRCS_DIR)$(BUILTINS_DIR)builtins_utils.c\
						$(SRCS_DIR)$(BUILTINS_DIR)cd.c\
						$(SRCS_DIR)$(BUILTINS_DIR)echo.c\
						$(SRCS_DIR)$(BUILTINS_DIR)env.c\
						$(SRCS_DIR)$(BUILTINS_DIR)export_utils.c\
						$(SRCS_DIR)$(BUILTINS_DIR)export.c\
						$(SRCS_DIR)$(BUILTINS_DIR)msh_exit.c\
						$(SRCS_DIR)$(BUILTINS_DIR)pwd.c\
						$(SRCS_DIR)$(BUILTINS_DIR)unset.c\
						\
						$(SRCS_DIR)$(LEX_DIR)handle_quotes.c\
						$(SRCS_DIR)$(LEX_DIR)lexer_list.c\
						$(SRCS_DIR)$(LEX_DIR)lexer_utils.c\
						$(SRCS_DIR)$(LEX_DIR)lexer.c\
						$(SRCS_DIR)$(LEX_DIR)lexer_list2.c\
						\
						$(SRCS_DIR)$(HEREDOC_DIR)heredoc_utils.c\
						$(SRCS_DIR)$(HEREDOC_DIR)heredoc_sigs_tempfiles.c\
						$(SRCS_DIR)$(HEREDOC_DIR)heredoc.c\
						$(SRCS_DIR)$(HEREDOC_DIR)unlink_hd.c\
						\
						$(SRCS_DIR)$(EXPAND_DIR)expand_utils.c\
						$(SRCS_DIR)$(EXPAND_DIR)expand_var.c\
						$(SRCS_DIR)$(EXPAND_DIR)expand.c\
						$(SRCS_DIR)$(EXPAND_DIR)strip_quotes.c\
						\
						$(SRCS_DIR)$(EXEC_DIR)child_processes.c\
						$(SRCS_DIR)$(EXEC_DIR)exec_redirs.c\
						$(SRCS_DIR)$(EXEC_DIR)exec_utils.c\
						$(SRCS_DIR)$(EXEC_DIR)execute.c\
						$(SRCS_DIR)$(EXEC_DIR)pipes.c\
						$(SRCS_DIR)$(EXEC_DIR)redirs_in_main.c\
						$(SRCS_DIR)$(EXEC_DIR)wait.c\

OBJS				=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

$(OBJS_DIR)%.o:			$(SRCS_DIR)%.c
						@mkdir -p $(dir $@)
						$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:					$(NAME)

$(NAME):				$(OBJS) $(INC_DIR)$(HEADER)
						@echo "Compiling Libft ..."
						@make -s -C $(LIBFT_DIR)
						@echo "Libft Done !"
						$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT_DIR)$(LIBFT) -lreadline -o $(NAME)

clean:
						@make fclean -C $(LIBFT_DIR)
						$(RM) $(OBJS_DIR)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re
