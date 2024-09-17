/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:36:16 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/17 14:12:59 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmdtable(t_shell shell)
{
	t_parser *current_node = shell.parser;
	int cmd_num = 1;

	printf("Command Table:\n");
	while (current_node)
	{
		printf("\n	Command %d:\n", cmd_num++);
		t_parser *cmd = (t_parser *)current_node;
		printf("		infile: %d\n", cmd->infile);
		printf("		outfile: %d\n", cmd->outfile);
		printf("		full_path: %s\n", cmd->full_path ? cmd->full_path : "NULL (because command is a builtin)");
		int i = 0;
		if (cmd->full_cmd)
		{
			while (cmd->full_cmd)
			{
				printf("		Arg[%d]: %s\n", i, (char *)cmd->full_cmd->content);
				i++;
				cmd->full_cmd = cmd->full_cmd->next;
			}
		}
		else
			printf("  No command arguments.\n");
		current_node = current_node->next;
	}
}

static t_parser *new_cmd_node()
{
	t_parser *cmd = malloc(sizeof(t_parser));
	if (!cmd)
		return NULL;
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;   // Default to standard input
	cmd->outfile = STDOUT_FILENO; // Default to standard output
	cmd->next = NULL;
	return cmd;
}

void parser(t_shell *shell)
{
	t_parser *parser;
	t_lexer *lexer;
	t_list	*node_input;

	shell->parser = new_cmd_node();
	parser = shell->parser;
	lexer = shell->lexer;
	
	int *pipefd;
	pipefd = piping();
	while (lexer)
	{
		node_input = ft_lstnew(lexer->input);
		if (lexer->type == TOKEN_ARG)
			ft_lstadd_back(&parser->full_cmd, node_input);
		else if (lexer->type == TOKEN_REDIR_IN)
			parser->infile = 1;
		else if (lexer->type == TOKEN_REDIR_OUT)
		{
			
			parser->outfile = 0;
		}
		//free(node_input); 
		lexer = lexer->next;
		if (lexer && lexer->type == TOKEN_PIPE)
		{
			parser->outfile = pipefd[1];
			parser->next = new_cmd_node();
			parser = parser->next;
			parser->infile = pipefd[0];
		}
	}
	
}
