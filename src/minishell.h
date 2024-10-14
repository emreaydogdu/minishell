/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/10/14 12:35:57 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
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
}	t_token_type;

typedef struct s_lexer
{
	char			*input;
	size_t			pos;
	int				type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_parser
{
	t_list			*args;
	int				infile;
	int				outfile;
	struct s_parser	*next;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			*cmdline;
	char			*tmp_output;
	int				exit_status;
	struct s_lexer	*lexer;
	struct s_parser	*parser;
	struct s_env	*env;
}	t_shell;

void	lexer(t_shell *shell);
void	expander(t_shell *shell);
void	parser(t_shell *shell);

void	init_env(t_shell *shell, char **env);
int		env_push(t_env **env, char* key, char *value);
int		env_pop(t_env **env, char *key);

/* BUILTINS */
int		is_bin(char *cmd);
void	exec_bin(t_shell *shell, char *cmd);
void	exec_echo(t_shell *parser);
void	exec_cd(t_shell *shell);
void	exec_pwd(t_shell *shell);
void	exec_env(t_shell shell);
void	exec_export(t_shell *shell);
void	exec_unset(t_shell *shell);
void	exec_exit(t_shell *shell);
void	exec_start(t_shell *shell);
void	exec_cmd(char *path, t_list *args);

/* todo: DELETE */
void	print_lexer(t_shell shell);
void	print_cmdtable(t_shell shell);

int		correct_single_quotes(char * input);
void	write_single_quotes(char *input);

/* HELPER FUNCTIONS */
char	*trim(char *str);
void	error(t_shell *shell, char *err_msg, char *args);

// Cleaning
void	cleanup(t_shell *shell);
void	free_lexer(t_lexer *lexer);
void	free_parser(t_parser *parser);
void	free_env(t_env *env);

int		*piping();
char 	*get_external_cmd_path(char *cmd);
char	*ft_getenv(t_shell *shell, char *key);

#endif
