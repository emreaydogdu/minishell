/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/09 18:25:52 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"

# define BANNER "\
######################################################################################\n\
██╗  ██╗██████╗ ███████╗██╗  ██╗███████╗██╗     ██╗ \n\
██║  ██║╚════██╗██╔════╝██║  ██║██╔════╝██║     ██║ \n\
███████║ █████╔╝███████╗███████║█████╗  ██║     ██║ \n\
╚════██║██╔═══╝ ╚════██║██╔══██║██╔══╝  ██║     ██║ \n\
     ██║███████╗███████║██║  ██║███████╗███████╗███████╗ \n\
     ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n\
 \n\
 ██████╗██╗  ██╗ █████╗ ██╗  ██╗██╗██████╗       ███████╗███╗   ███╗██████╗ ███████╗ \n\
██╔════╝██║  ██║██╔══██╗██║ ██╔╝██║██╔══██╗      ██╔════╝████╗ ████║██╔══██╗██╔════╝ \n\
██║     ███████║███████║█████╔╝ ██║██████╔╝█████╗█████╗  ██╔████╔██║██████╔╝█████╗ \n\
██║     ██╔══██║██╔══██║██╔═██╗ ██║██╔══██╗╚════╝██╔══╝  ██║╚██╔╝██║██╔══██╗██╔══╝ \n\
╚██████╗██║  ██║██║  ██║██║  ██╗██║██████╔╝      ███████╗██║ ╚═╝ ██║██║  ██║███████╗ \n\
 ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═════╝       ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝ \n\
######################################################################################\n\
"

typedef enum	s_token_type
{
	TOKEN_ARG = 0,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_COMMAND
	/* TOKEN_WORD,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_SEMICOLON,
	TOKEN_NEWLINE,
	TOKEN_EOF */
}			t_token_type;

typedef enum s_std_cmd
{
	CMD_CD = 0,
	CMD_ECHO,
	CMD_EXIT,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV
}			t_std_cmd;

typedef struct s_lexer
{
	char			*input;
	size_t			pos;
	int				type;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_parser
{
	char					*cmd;
	int						std_cmd;
	struct s_parser_node	*left;
	struct s_parser_node	*right;
}				t_parser;

typedef struct s_shell
{
	char			*cmdline;
	struct s_lexer	*lexer;
	struct s_parser	*parser;
	struct s_env	*env;
}	t_shell;


typedef struct s_prompt
{
	t_list	*cmds;
	pid_t	pid;
}	t_prompt;

typedef struct s_cmd
{
	t_list	*full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	lexer(t_shell *shell);
void	expander(t_shell *shell);
void	parser(t_shell *shell, t_prompt *prompt);

void	init_env(t_shell *shell, char **env);
int		env_push(t_env **env, char* key, char *value);
int		env_pop(t_env **env, char *key);

/* BUILTINS */
int		is_bin(char *cmd);
void	exec_bin(t_shell shell, char *cmd, char **args);
void	exec_echo(char **args);
void	exec_cd(char **args);
void	exec_pwd(void);
void	exec_env(t_shell *shell);
void	exec_export(t_shell *shell, char **args);
void	exec_unset(t_shell *shell, char **args);

/* todo: DELETE */
void	print_lexer(t_shell shell);
void	print_cmdtable(t_prompt *prompt);
int		is_builtin(char *cmd);

int		correct_single_quotes(char * input);
void	write_single_quotes(char *input);

#endif
