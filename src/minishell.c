/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/17 14:10:30 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_shell *shell)
{
	if (shell->lexer)
	{
		free_lexer(shell->lexer);
		shell->lexer = NULL;
	}
	if (shell->parser)
	{
		free_parser(shell->parser);
		shell->parser = NULL;
	}
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
/* 	
	if (shell->cmdline)
	{
		free(shell->cmdline);
		shell->cmdline = NULL;
	}
	 */
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer *tmp;
	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->input)
		{
			free(lexer->input);
			lexer->input = NULL;
		}
		free(lexer);
		lexer = tmp;
	}
}

void	free_parser(t_parser *parser)
{
	t_parser *tmp;
	
	t_list *tmp_fullcmd;
	while (parser)
	{
		tmp = parser->next;
		while (parser->full_cmd)
		{
			tmp_fullcmd = parser->full_cmd->next;
			if(parser->full_cmd)
			{
				free(parser->full_cmd);
				parser->full_cmd = NULL;
			}
			parser->full_cmd = tmp_fullcmd;
		}
		free(parser);
		parser = tmp;
	}
}
void	free_env(t_env *env)
{
	t_env *tmp;
	while(env)
	{
		tmp = env->next;
		if (env->key)
		{
			free(env->key);
			env->key = NULL;
		}
		free(env);
		env = tmp;
	}
}

static void	minishell(void)
{
	struct s_shell	shell;

	shell.cmdline = NULL;
	shell.env = NULL;
	shell.lexer = NULL;
	shell.parser = NULL;
	while (1)
	{
 		shell.cmdline = readline("\033[36;1m ➜ minishell$ \033[0m");
		if (!shell.cmdline)
			return ; 
		shell.cmdline[ft_strlen(shell.cmdline)] = '\0';

		//shell.cmdline = "echo 'hello' 'Emre'";
 		//add_history(shell.cmdline);
		lexer(&shell);
		expander(&shell);
		print_lexer(shell);// optional only printing: delete after finish
		printf("------------------------------------------------\n");

		parser(&shell);
		print_cmdtable(shell);
		printf("------------------------------------------------\n");
		while (shell.parser)
		{
			while (shell.parser->full_cmd)
			{
				char *content = (char *)shell.parser->full_cmd->content;
				shell.parser->full_cmd = shell.parser->full_cmd->next;
				exec_bin(&shell, content, NULL);
				break ;
			}
			shell.parser = shell.parser->next;
		}
		cleanup(&shell);
		printf("\n");
		//free(shell.cmdline);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	minishell();

/*
	char *cmd = "export";
	char *args[] = {"unset", "A=Hello", "B=GoodBye", "C=Emre", NULL};
	char *args2[] = {"unset", "MAIL", "C", NULL};

	t_shell	shell;
	shell.env = NULL;
	init_env(&shell, env);
	exec_env(&shell);
*/
	return (0);
}
