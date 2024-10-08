/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/04 11:57:19 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
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
}				t_shell;


typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}	t_prompt;

typedef struct s_cmd
{
	t_list	*full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}	t_mini;


void	lexer(t_shell *shell);
void	expander(t_shell *shell);
void	parser(t_lexer *lexer, t_prompt *prompt);

/* todo: DELETE */
void	print_lexer(t_shell shell);
#endif
