/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:36:16 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/01 18:29:08 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <string.h>

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

void parse_tokens(t_lexer *lexer, t_prompt *prompt)
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