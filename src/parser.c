/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:36:16 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/03 23:11:20 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <string.h>

void print_cmd(t_mini *cmd)
{
	int i = 0;

	printf("		infile: %d\n", cmd->infile);
	printf("		outfile: %d\n", cmd->outfile);
	printf("		full_path: %s\n", cmd->full_path ? cmd->full_path : "NULL (because command is a builtin)");
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

}

void print_cmdtable(t_prompt *prompt)
{
	t_list *current_node = prompt->cmds;
	int cmd_num = 1;

	printf("Command Table:\n");
	while (current_node)
	{
		t_mini *cmd = (t_mini *)current_node->content;
		printf("\n	Command %d:\n", cmd_num++);
		print_cmd(cmd);
		current_node = current_node->next;
	}
}

// Helper function to create a new command
t_mini *create_cmd()
{
	t_mini *cmd = malloc(sizeof(t_mini));
	if (!cmd)
		return NULL;
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;  // Default to standard input
	cmd->outfile = STDOUT_FILENO; // Default to standard output
	return cmd;
}

// Add the command to the prompt's command list
void add_cmd_to_prompt(t_prompt *prompt, t_mini *cmd)
{
	t_list *new_node = ft_lstnew(cmd);
	if (!new_node)
		return; // Handle memory allocation failure
	ft_lstadd_back(&(prompt->cmds), new_node);
}

void parser(t_lexer *lexer, t_prompt *prompt)
{
	t_mini *cmd = create_cmd();
	while (lexer)
	{
		if (lexer->type == TOKEN_COMMAND || lexer->type == TOKEN_ARG)
			ft_lstadd_back(&cmd->full_cmd, ft_lstnew(lexer->input));
		else if (lexer->type == TOKEN_REDIR_IN)
			cmd->infile = 1;
		else if (lexer->type == TOKEN_REDIR_OUT)
			cmd->outfile = 0;

		lexer = lexer->next;
		if (lexer && lexer->type == TOKEN_PIPE) // End of a command, start a new one
		{
			add_cmd_to_prompt(prompt, cmd);
			cmd = create_cmd();
		}
	}

	if (cmd->full_cmd != NULL) // Add the last command if it exists
	{
		add_cmd_to_prompt(prompt, cmd);
	}
}